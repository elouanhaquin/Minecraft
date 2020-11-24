#include "stdafx.h"

#include <RigidBodyData.h>

using namespace PhysicsEngineNS;

RigidBodyData::RigidBodyData(const float& p_mass, const bool& p_applyGravity,
	const bool& p_isKinematic, const glm::vec3& p_velocity)
	: m_mass{ p_mass }, m_applyGravity{ p_applyGravity },
	m_isKinematic{ p_isKinematic }, m_velocity{ p_velocity }, m_isJumping{false}
{
}

RigidBodyData::~RigidBodyData()
{
}

float& RigidBodyData::Mass()
{
	return m_mass;
}

glm::vec3& RigidBodyData::Velocity()
{
	return m_velocity;
}

bool& RigidBodyData::HasGravity()
{
	return m_applyGravity;
}

bool& RigidBodyData::IsKinematic()
{
	return m_isKinematic;
}

bool& PhysicsEngineNS::RigidBodyData::IsJumping()
{
	return m_isJumping;
}

bool& PhysicsEngineNS::RigidBodyData::IsOnTheFloor()
{
	return m_isOnTheFloor;
}

void RigidBodyData::AddForce(glm::vec3& p_force, double& p_deltaTime)
{
	if (m_isKinematic)
		return;

	m_velocity += p_force; // m_mass;

	m_velocity.x *= p_deltaTime;
	m_velocity.y *= p_deltaTime;
	m_velocity.z *= p_deltaTime;

	m_position += m_velocity;
}

glm::vec3& RigidBodyData::Position()
{
	return m_position;
}