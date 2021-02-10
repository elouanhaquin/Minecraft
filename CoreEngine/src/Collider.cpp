#include "stdafx.h"

#include <Collider.h>
#include <GameObject.h>
#include <Transform.h>
#include <SphereCollider.h>
#include <type_traits>

using namespace CoreEngineNS;

Collider::Collider(Primitive* aPrimivite)
{
	m_primitive = aPrimivite;
}

CoreEngineNS::Collider::~Collider()
{

	delete m_primitive;

}


Primitive* Collider::GetCollider()
{
	return m_primitive;
}
