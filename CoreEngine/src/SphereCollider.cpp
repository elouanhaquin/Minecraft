#include "stdafx.h"

#include <SphereCollider.h>
#include <GameObject.h>
#include <Transform.h>

using namespace CoreEngineNS;

SphereCollider::SphereCollider(float aRadius) : Collider(new Sphere(aRadius))
{
	m_sphere = static_cast<Sphere*>(m_primitive);
}

void SphereCollider::Update()
{
	m_sphere->Position() = m_parent->GetComponent<Transform>().GetPosition();
}

SphereCollider::~SphereCollider()
{

}

Primitive* SphereCollider::GetCollider()
{
	return m_sphere;
}