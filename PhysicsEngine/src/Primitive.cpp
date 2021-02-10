#include "stdafx.h"
#include <Primitive.h>

using namespace PhysicsEngineNS;

Primitive::Primitive()
{
}



glm::vec3& PhysicsEngineNS::Primitive::Position()
{
	return m_position;
}

const EPrimitiveType PhysicsEngineNS::Primitive::Type()
{
	return m_type;
}
