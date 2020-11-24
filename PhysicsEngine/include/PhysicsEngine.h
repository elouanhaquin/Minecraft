#pragma once

#include <PhysicsEngineAPI.h>
#include "Primitive.h"
#include "Sphere.h"
#include <AABB.h>
#include <RigidBodyData.h>

namespace PhysicsEngineNS
{
	using Force = glm::vec3;

	struct PHYSICSENGINE_API CollisionInformation
	{
		glm::vec3			HitPoint;
		glm::vec3			Normal;
		const Primitive*	pPrimitive;
		EPrimitiveType		Type;

		CollisionInformation(const Primitive* aPrimitive = nullptr, EPrimitiveType aType = UNKNOWN_TYPE)
			: pPrimitive(aPrimitive)
			, Type(aType)
		{}
	};

	class PHYSICSENGINE_API PhysicsEngine
	{
	public:
		PhysicsEngine(double* p_deltaTime);
		~PhysicsEngine();

		bool Intersect(Primitive* aPrimtive1, Primitive* aPrimitive2);
		void ApplyGravity(RigidBodyData* p_rigidBodyData);
		void ResolveCollision(RigidBodyData* p_player, Primitive* p_playerPrimitive, RigidBodyData* p_otherRb, Primitive* p_otherCollider);

	private:
		double* m_deltaTime;
	};
}