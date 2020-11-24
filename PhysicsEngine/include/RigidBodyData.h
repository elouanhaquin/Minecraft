#pragma once

#include <PhysicsEngineAPI.h>

namespace PhysicsEngineNS
{
	class PHYSICSENGINE_API RigidBodyData
	{
	private:
		float m_mass;
		bool m_applyGravity;
		bool m_isKinematic;
		glm::vec3 m_velocity;
		glm::vec3 m_position;
		bool m_isJumping;
		bool m_isOnTheFloor;

	public:
		RigidBodyData(const float& p_mass, const bool& p_applyGravity,
			const bool& p_isKinematic, const glm::vec3& p_velocity);
		~RigidBodyData();

		float& Mass();
		glm::vec3& Velocity();
		bool& HasGravity();
		bool& IsKinematic();
		bool& IsJumping();
		bool& IsOnTheFloor();
		glm::vec3& Position();

		void AddForce(glm::vec3& p_force, double& p_deltaTime);
	};
}