// PhysicsEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "PhysicsEngine.h"

using namespace PhysicsEngineNS;

Force Gravity(0.0f, -12.0f, 0.0f);
Force falling(0.0f, -175.0f, 0.0f);
float fallAcceleration = 0.0f;

PhysicsEngine::PhysicsEngine(double* p_deltaTime) : m_deltaTime {p_deltaTime}
{
	std::cout << "Physics Engine On" << std::endl;
}

PhysicsEngine::~PhysicsEngine()
{
	std::cout << "Physics Engine Off" << std::endl;
}

bool PhysicsEngine::Intersect(Primitive* aPrimitive1, Primitive* aPrimitive2)
{
	bool intersect = false;

	if (aPrimitive1 == nullptr || aPrimitive2 == nullptr)
		return intersect;

	if (aPrimitive1->Type() == EPrimitiveType::SPHERE_TYPE && aPrimitive2->Type() == EPrimitiveType::SPHERE_TYPE)
	{
		Sphere* sphere1 = static_cast<Sphere*>(aPrimitive1);
		Sphere* sphere2 = static_cast<Sphere*>(aPrimitive2);

		float distance = sqrt(pow(aPrimitive1->Position().x - aPrimitive2->Position().x, 2.0) + pow(aPrimitive1->Position().y - aPrimitive2->Position().y, 2.0) + pow(aPrimitive1->Position().z - aPrimitive2->Position().z, 2.0));

		float minDistance = sphere1->Radius() + sphere2->Radius();
		minDistance *= minDistance;

		if (distance <= minDistance)
			return true;
	}

	else if(aPrimitive1->Type() == EPrimitiveType::AABB_TYPE && aPrimitive2->Type() == EPrimitiveType::AABB_TYPE)
	{
		AABB* aabb1 = static_cast<AABB*>(aPrimitive1);
		AABB* aabb2 = static_cast<AABB*>(aPrimitive2);

		return (aabb1->GetMaxPoint().x >= aabb2->GetMinPoint().x &&
			aabb1->GetMinPoint().x < aabb2->GetMaxPoint().x &&
			aabb1->GetMaxPoint().y > aabb2->GetMinPoint().y &&
			aabb1->GetMinPoint().y < aabb2->GetMaxPoint().y &&
			aabb1->GetMaxPoint().z > aabb2->GetMinPoint().z &&
			aabb1->GetMinPoint().z < aabb2->GetMaxPoint().z);
	}
	else if ((aPrimitive1->Type() == EPrimitiveType::AABB_TYPE && aPrimitive2->Type() == EPrimitiveType::SPHERE_TYPE) ||
		(aPrimitive1->Type() == EPrimitiveType::SPHERE_TYPE && aPrimitive2->Type() == EPrimitiveType::AABB_TYPE))
	{
		Sphere*    sphere;
		AABB*    aabb;

		if (aPrimitive1->Type() == EPrimitiveType::SPHERE_TYPE)
		{
			sphere = static_cast<Sphere*>(aPrimitive1);
			aabb = static_cast<AABB*>(aPrimitive2);
		}
		else
		{
			sphere = static_cast<Sphere*>(aPrimitive2);
			aabb = static_cast<AABB*>(aPrimitive1);
		}
		float temp = sphere->Radius();
		const glm::vec3 centerToClosestPoint = glm::clamp(sphere->Position(), aabb->GetMinPoint(), aabb->GetMaxPoint()) - sphere->Position();
		return (glm::dot(centerToClosestPoint, centerToClosestPoint) < sphere->Radius()* sphere->Radius());
	}

	return intersect;
}

float timerCount = 0.0f;
float fallTime = 0.0f;
float timeAtFallStart = 0.0f;
bool isFallingStart = false;
void PhysicsEngine::ApplyGravity(RigidBodyData* p_rigidBodyData)
{
	if (p_rigidBodyData->IsKinematic())
		return;

	if (p_rigidBodyData->HasGravity())
	{
		

		if (!p_rigidBodyData->IsOnTheFloor() && !p_rigidBodyData->IsJumping())
		{
			if (isFallingStart)
			{
				timeAtFallStart = glfwGetTime();
				fallAcceleration = 0.0f;
				fallTime = 0.0f;
				timeAtFallStart = 0.0f;
				isFallingStart = true;
			}

			fallTime = glfwGetTime() - timeAtFallStart;
			if (fallTime - timerCount >= 1.0f / 60.0f)
			{ 
				fallAcceleration += 0.003428f * ((fallTime - timerCount) / (1.0f / 60.0f) - 0.5f);   // Acceleration of falling
				if (fallAcceleration >= 1.0f)
					fallAcceleration = 1.0f;
				timerCount = fallTime;
			}
		}
		if (p_rigidBodyData->IsOnTheFloor() || p_rigidBodyData->IsJumping())
		{
			timerCount = 0.0f;
			fallAcceleration = 0.0f;
			fallTime = 0.0f;
			timeAtFallStart = 0.0f;
			isFallingStart = true;
		}

		glm::vec3 force = Gravity + (falling * fallAcceleration);
		p_rigidBodyData->AddForce(force, *m_deltaTime);
		// Debug for Beta Prez !!!
		
		/*if (p_rigidBodyData->Position().y <= 30.0f) // If is on the floor
		{
			p_rigidBodyData->Position().y = 30.0f; // TO DO set to the position of the block downstairs
			p_rigidBodyData->IsOnTheFloor() = true;
		}
		else
			p_rigidBodyData->IsOnTheFloor() = false;*/
	}
}

void PhysicsEngine::ResolveCollision(RigidBodyData* p_player, Primitive* p_playerPrimitive, RigidBodyData* p_otherRb, Primitive* p_otherCollider)
{
	if (p_otherCollider->Type() == EPrimitiveType::SPHERE_TYPE)
	{
		Sphere* playerSphere		= static_cast<Sphere*>(p_playerPrimitive);
		Sphere* otherSphere			= static_cast<Sphere*>(p_otherCollider);

		glm::vec3 direction			= (p_player->Position() - p_otherRb->Position());
		p_player->Position()		+= glm::normalize(direction) * ((playerSphere->Radius() + otherSphere->Radius()) - glm::distance(p_player->Position(), p_otherRb->Position()));

	}

	if (p_otherCollider->Type() == EPrimitiveType::AABB_TYPE)
	{
		Sphere* playerSphere = static_cast<Sphere*>(p_playerPrimitive);
		AABB* otherBox = static_cast<AABB*>(p_otherCollider);

		glm::vec3 direction = p_otherCollider->Position() - p_player->Position();

		glm::vec3 distance1 = otherBox->GetMinPoint() - playerSphere->Radius();
		glm::vec3 distance2 = playerSphere->Radius() - otherBox->GetMaxPoint();

		glm::vec3 distances;
		distances.x = (distance1.x > distance2.x) ? distance1.x : distance2.x;
		distances.y = (distance1.y > distance2.y) ? distance1.y : distance2.y;
		distances.z = (distance1.z > distance2.z) ? distance1.z : distance2.z;

		float maxDistance = distances.x;

		if (distances.y > maxDistance) maxDistance = distances.y;
		if (distances.z > maxDistance) maxDistance = distances.z;

		maxDistance -= playerSphere->Radius();

		glm::vec3 closestPoint;

		closestPoint.x = ( p_player->Position().x <  otherBox->GetMinPoint().x) ? otherBox->GetMinPoint().x : ( p_player->Position().x >otherBox->GetMaxPoint().x) ? otherBox->GetMaxPoint().x : p_player->Position().x;
		closestPoint.y = (p_player->Position().y <  otherBox->GetMinPoint().y) ? otherBox->GetMinPoint().y : ( p_player->Position().y > otherBox->GetMaxPoint().y) ? otherBox->GetMaxPoint().y :  p_player->Position().y;
		closestPoint.z = ( p_player->Position().z <  otherBox->GetMinPoint().z) ? otherBox->GetMinPoint().z : ( p_player->Position().z > otherBox->GetMaxPoint().z) ? otherBox->GetMaxPoint().z :  p_player->Position().z;

		//closestPoint = glm::clamp(p_player->Position(), otherBox->GetMinPoint(), otherBox->GetMaxPoint() - p_player->Position());

		glm::vec3 normal = p_player->Position() - closestPoint;

		p_player->Position() = closestPoint + (glm::normalize(normal) * playerSphere->Radius());

		p_player->Velocity() = glm::vec3(0);
	}

}

