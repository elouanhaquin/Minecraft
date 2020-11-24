#pragma once

#include <GameObject.h>
#include <Transform.h>
#include <SimplexNoise.h>

namespace CoreEngineNS
{
	class Player : public GameObject
	{
	private:
		Transform* transform;
		SimplexNoise simplex;
		float m_movementSpeed;

		glm::vec3 m_jumpForce;
		float m_jumpSpeed;

		bool isCreativeMode;

	public:
		~Player();

		void Awake() override;
		void Update() override;
		void FixedUpdate() override;

		bool& IsOnTheFloor();
	};
}