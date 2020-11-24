#include "stdafx.h"

#include <Sphere.h>

using namespace PhysicsEngineNS;

Sphere::Sphere( const float& p_radious): m_radius{ p_radious }
{
	m_type = EPrimitiveType::SPHERE_TYPE;
}

Sphere::~Sphere()
{
}

float Sphere::Radius()
{
	return m_radius;
}
