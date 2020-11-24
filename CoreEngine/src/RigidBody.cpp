#include "stdafx.h"

#include <RigidBody.h>
#include <GameObject.h>
#include <Transform.h>
#include <Time.h>

using namespace CoreEngineNS;
using namespace TimeNS;

RigidBody::RigidBody(const float& p_mass, const bool& p_applyGravity, const bool& p_isKinematic, const glm::vec3& p_velocity)
{
	m_rigidBody = new RigidBodyData(p_mass, p_applyGravity, p_isKinematic, p_velocity);
}

RigidBody::~RigidBody()
{
}

void RigidBody::Awake()
{
	m_rigidBody->Position() = m_parent->GetComponent<Transform>().GetPosition();
}

RigidBodyData* RigidBody::GetData()
{
	return m_rigidBody;
}

float& RigidBody::Mass()
{
	return m_rigidBody->Mass();
}

glm::vec3& RigidBody::Velocity()
{
	return m_rigidBody->Velocity();
}

bool& RigidBody::HasGravity()
{
	return m_rigidBody->HasGravity();
}

bool& RigidBody::IsKinematic()
{
	return m_rigidBody->IsKinematic();
}

bool& CoreEngineNS::RigidBody::IsJumping()
{
	return m_rigidBody->IsJumping();
}

bool& CoreEngineNS::RigidBody::IsOnTheFloor()
{
	return m_rigidBody->IsOnTheFloor();
}

void RigidBody::AddForce(glm::vec3& p_force, double& p_deltaTime)
{
	m_rigidBody->AddForce(p_force, p_deltaTime);


	if (m_rigidBody->IsKinematic())
		return;

	//m_rigidBody->Velocity() += p_force; // Mass();
}

void RigidBody::Update()
{
	//m_rigidBody->Position() = m_parent->GetComponent<Transform>().GetPosition();
	 m_parent->GetComponent<Transform>().SetPosition(m_rigidBody->Position());

}