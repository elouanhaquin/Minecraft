#pragma once

#include <Component.h>
#include <Sphere.h>
#include <Primitive.h>
#include <AABB.h>

using namespace PhysicsEngineNS;

namespace CoreEngineNS
{
	class Collider: public Component
	{
	protected:
		Primitive* m_primitive;

	public:
		Collider(Primitive* aPrimivite);
		~Collider();

		virtual Primitive* GetCollider();

	};
}