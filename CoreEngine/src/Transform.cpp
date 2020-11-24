#include "stdafx.h"

#include <Transform.h>
#include <GameObject.h>
#include <RigidBodyData.h>
#include <RigidBody.h>

using namespace CoreEngineNS;

Transform::Transform() : m_position{glm::vec3(0, 0, 0)}, m_scale {glm::vec3(1, 1, 1)}, m_oldPositionY(0)
{
}

Transform::~Transform()
{
}

const glm::vec3& Transform::GetPosition() const
{
	return m_position;
}

const glm::vec3& CoreEngineNS::Transform::GetForward() const
{
	return m_forward;
}

void Transform::SetPosition(const glm::vec3& p_position)
{
	m_position = p_position;

	if (m_parent->HasComponent<RigidBody>())
		m_parent->GetComponent<RigidBody>().GetData()->Position() = p_position;
	
}

void Transform::SetPositionX(const float& p_x)
{
	m_position = glm::vec3(p_x, m_position.y, m_position.z);
}

void Transform::SetPositionY(const float& p_y)
{
	m_position = glm::vec3(m_position.x, p_y, m_position.z);
}

void Transform::SetPositionZ(const float& p_z)
{
	m_position = glm::vec3(m_position.x, m_position.y, p_z);
}

void CoreEngineNS::Transform::SetForward(const glm::vec3 & p_forward)
{
	m_forward = p_forward;
}

const glm::vec3& Transform::GetScale() const
{
	return m_scale;
}

//int& CoreEngineNS::Transform::GetOldPositionY()
//{
//	return m_oldPositionY;
//}

void Transform::SetScale(const glm::vec3& p_scale)
{
	m_scale = p_scale;
}
