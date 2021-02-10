#include "stdafx.h"

#include <BoxCollider.h>
#include <Transform.h>
#include <GameObject.h>

using namespace CoreEngineNS;

/*BoxCollider::BoxCollider(glm::vec3 p_min, glm::vec3 p_max) : Collider (new AABB(p_min, p_max))
{
	m_min = p_min;
	m_max = p_max;

	m_box = static_cast<AABB*>(m_primitive);
}*/

BoxCollider::BoxCollider(glm::vec3 pos, glm::vec3 p_min, glm::vec3 p_max) : Collider(new AABB(p_min, p_max))
{
	m_min = p_min;
	m_max = p_max;

	m_box = static_cast<AABB*>(m_primitive);

	m_primitive->Position() = pos;

	m_minOffset = m_min - pos;
	m_maxOffset = m_max + pos;
}

void BoxCollider::Awake()
{
	m_primitive->Position() = m_parent->GetComponent<Transform>().GetPosition();

	m_minOffset = m_min - m_parent->GetComponent<Transform>().GetPosition();
	m_maxOffset = m_max + m_parent->GetComponent<Transform>().GetPosition();
}

/*BoxCollider::~BoxCollider()
{
	delete m_box;
}*/

void BoxCollider::Update()
{
	m_box->Position() = m_parent->GetComponent<Transform>().GetPosition();

	m_box->GetMinPoint() = m_box->Position() + m_minOffset;
	m_box->GetMaxPoint() = m_box->Position() + m_maxOffset;


}