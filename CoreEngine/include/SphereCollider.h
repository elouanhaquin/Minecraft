#pragma once

#include <Collider.h>

using namespace PhysicsEngineNS;

namespace CoreEngineNS
{
	class SphereCollider : public Collider
	{
	public:


		SphereCollider(float aRadius);
		~SphereCollider();

		void Update() override;

		Primitive* GetCollider() override;

	private:
		

		Sphere* m_sphere;

	};
}
