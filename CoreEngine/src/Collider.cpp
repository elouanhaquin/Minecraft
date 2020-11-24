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

Collider::~Collider()
{
}

Primitive* Collider::GetCollider()
{
	return m_primitive;
}
