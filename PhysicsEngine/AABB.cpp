
#include "stdafx.h"
#include <AABB.h>

using namespace PhysicsEngineNS;


AABB::AABB(glm::vec3 aPointMin, glm::vec3 aPointMax, glm::vec3 aPosition)
{
	m_pointMax = aPointMax + aPosition;
	m_pointMin = aPointMin + aPosition;

	m_type = EPrimitiveType::AABB_TYPE;
}


glm::vec3& AABB::GetMinPoint()
{
	return m_pointMin;
}

glm::vec3& AABB::GetMaxPoint()
{
	return m_pointMax;
}

