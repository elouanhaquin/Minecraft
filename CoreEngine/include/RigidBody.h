#pragma once

#include <Component.h>
#include <RigidBodyData.h>

using namespace PhysicsEngineNS;

namespace CoreEngineNS
{
	class RigidBody : public Component
	{
	private:
		RigidBodyData* m_rigidBody;

	public:
		RigidBody(const float& p_mass = 1, const bool& p_applyGravity = true,
			const bool& p_isKinematic = false, const glm::vec3& p_velocity = glm::vec3(0));
		~RigidBody();

		RigidBodyData* GetData();

		float& Mass();
		glm::vec3& Velocity();
		bool& HasGravity();
		bool& IsKinematic();
		bool& IsJumping();
		bool& IsOnTheFloor();

		void AddForce(glm::vec3& p_force, double& p_deltaTime);

		void Awake() override;
		void Update() override;
	};
}