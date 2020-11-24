#pragma once

#include <PhysicsEngineAPI.h>
#include <Primitive.h>

namespace PhysicsEngineNS
{
	class PHYSICSENGINE_API Sphere : public Primitive
	{
	private:
		float m_radius;

	public:
		Sphere(const float& p_radious = 0.5f);
		~Sphere();

		float Radius();
	};
}