#include  "stdafx.h"

#include <cmath>
#include <Player.h>
#include <Input.h>
#include <Collider.h>
#include <Time.h>
#include <RigidBody.h>

using  namespace CoreEngineNS;
using namespace TimeNS;

Player::~Player()
{
}

void Player::Awake()
{
	std::cout << "Player Alive" << std::endl;
	transform = &this->GetComponent<Transform>();
	m_movementSpeed = 10.0f;
	transform->SetPosition(glm::vec3(0, 0, 0));
	m_jumpForce = glm::vec3(0, 900, 0);
	m_jumpSpeed = m_jumpForce.y / 35;
	isCreativeMode = false;
	simplex = SimplexNoise(0.015f, 8.0f, 1.0f, 1.0f);
}
float m_jumpAcceleration = 1.0f;
float m_jumpAccelerationCount = 0.02f;
float jumpTime = 0.0f;
float timeAtJumpStart = 0.0f;
float timerCount = 0.0f;

void Player::Update()
{
	GameObject::Update();
}

void Player::FixedUpdate()
{
	isCreativeMode = Input::CreativeMode();
	if (isCreativeMode)
		this->GetComponent<RigidBody>().HasGravity() = false;
	else
		this->GetComponent<RigidBody>().HasGravity() = true;

	if (Input::GetMovementDirection().x != 0 || Input::GetMovementDirection().z != 0)
	{
		glm::vec3 vectorUp(0, 1, 0);
		glm::vec3 frontDirection(0);
		if (isCreativeMode)
		{
			frontDirection = this->GetComponent<Transform>().GetForward() * (m_movementSpeed * static_cast<float>(Time::deltaTime));
		}
		else
		{
			glm::vec3 forward2D(this->GetComponent<Transform>().GetForward().x, 0, this->GetComponent<Transform>().GetForward().z);
			frontDirection = forward2D * (m_movementSpeed * static_cast<float>(Time::deltaTime));
		}
		glm::vec3 backDirection = frontDirection * -1.0f;

		// Go front
		if (Input::GetMovementDirection().z < 0)
		{
			m_movementSpeed = Input::Sprint() ? isCreativeMode ? 40 : 20 : 10;

			// Go front and left
			if (Input::GetMovementDirection().x < 0)
			{
				glm::vec3 leftDirection = glm::cross(this->GetComponent<Transform>().GetForward(), vectorUp) * -1.0f;
				leftDirection *= glm::length(frontDirection) / glm::length(leftDirection);

				glm::vec3 frontLeftDirection = frontDirection + leftDirection;
				frontLeftDirection *= glm::length(frontDirection) / glm::length(frontLeftDirection);
				this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + frontLeftDirection);
			}
			// Go front and right
			else if (Input::GetMovementDirection().x > 0)
			{
				glm::vec3 rightDirection = glm::cross(this->GetComponent<Transform>().GetForward(), vectorUp);
				rightDirection *= glm::length(frontDirection) / glm::length(rightDirection);

				glm::vec3 frontRightDirection = frontDirection + rightDirection;
				frontRightDirection *= glm::length(frontDirection) / glm::length(frontRightDirection);
				this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + frontRightDirection);
			}
			else
			{
				this->GetComponent<Transform>().SetPosition(glm::vec3(this->GetComponent<Transform>().GetPosition().x + frontDirection.x,
					this->GetComponent<Transform>().GetPosition().y + frontDirection.y,
					this->GetComponent<Transform>().GetPosition().z + frontDirection.z));
			}
		}
		// Go back
		else if (Input::GetMovementDirection().z > 0)
		{
			// if is Creative Mode can sprint in any direction
			m_movementSpeed = Input::Sprint() ? isCreativeMode ? 40 : 10 : 10;

			// Go back and left
			if (Input::GetMovementDirection().x < 0)
			{
				glm::vec3 leftDirection = glm::cross(this->GetComponent<Transform>().GetForward(), vectorUp) * -1.0f;
				leftDirection *= glm::length(frontDirection) / glm::length(leftDirection);

				glm::vec3 backLeftDirection = backDirection + leftDirection;
				backLeftDirection *= glm::length(frontDirection) / glm::length(backLeftDirection);
				this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + backLeftDirection);
			}
			// Go back and right
			else if (Input::GetMovementDirection().x > 0)
			{
				glm::vec3 rightDirection = glm::cross(this->GetComponent<Transform>().GetForward(), vectorUp);
				rightDirection *= glm::length(frontDirection) / glm::length(rightDirection);

				glm::vec3 backRightDirection = backDirection + rightDirection;
				backRightDirection *= glm::length(frontDirection) / glm::length(backRightDirection);
				this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + backRightDirection);
			}
			else
				this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + backDirection);
		}
		// Go only left
		else if (Input::GetMovementDirection().x < 0)
		{
			// if is Creative Mode can sprint in any direction
			m_movementSpeed = Input::Sprint() ? isCreativeMode ? 40 : 10 : 10;

			glm::vec3 leftDirection = glm::cross(this->GetComponent<Transform>().GetForward(), vectorUp) * -1.0f;
			leftDirection *= glm::length(frontDirection) / glm::length(leftDirection);
			this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + leftDirection);
		}
		// Go only right
		else if (Input::GetMovementDirection().x > 0)
		{
			// if is Creative Mode can sprint in any direction
			m_movementSpeed = Input::Sprint() ? isCreativeMode ? 40 : 10 : 10;

			glm::vec3 rightDirection = glm::cross(this->GetComponent<Transform>().GetForward(), vectorUp);
			rightDirection *= glm::length(frontDirection) / glm::length(rightDirection);
			this->GetComponent<Transform>().SetPosition(this->GetComponent<Transform>().GetPosition() + rightDirection);
		}
	}

	if (Input::GoDown())
	{
		glm::vec3 force(0.0f, -15.0f, 0.0f);
		this->GetComponent<RigidBody>().AddForce(force, Time::deltaTime);
	}
	if (Input::Jump())
	{
		if (!Input::CreativeMode())
		{
			if (this->GetComponent<RigidBody>().IsOnTheFloor())
			{
				this->GetComponent<RigidBody>().IsJumping() = true;
				this->GetComponent<RigidBody>().IsOnTheFloor() = false;
				timeAtJumpStart = glfwGetTime();
			}
		}
		else
		{
			glm::vec3 force(0.0f, 15.0f, 0.0f);
			this->GetComponent<RigidBody>().AddForce(force, Time::deltaTime);
		}
	}

	if (this->GetComponent<RigidBody>().IsJumping())
	{
		glm::vec3 force(0, m_jumpSpeed * m_jumpAcceleration, 0);
		this->GetComponent<RigidBody>().AddForce(force, Time::deltaTime);

		jumpTime = glfwGetTime() - timeAtJumpStart;
		if (jumpTime - timerCount >= TimeNS::Time::fixedDeltaTime)
		{
			m_jumpAcceleration -= m_jumpAccelerationCount * ((jumpTime - timerCount) / TimeNS::Time::fixedDeltaTime);
			timerCount = jumpTime;
		}

		if (m_jumpAcceleration <= 0.0f)
		{
			this->GetComponent<RigidBody>().IsJumping() = false;
			m_jumpAcceleration = 1.0f;
			jumpTime = 0.0f;
			timerCount = 0.0f;
		}
	}

	/*this->GetComponent<Transform>().SetPosition(glm::vec3(this->GetComponent<Transform>().GetPosition().x ,
														 (int)(simplex.fractal(7, (float)this->GetComponent<Transform>().GetPosition().x - 16, (float)this->GetComponent<Transform>().GetPosition().z - 16) * 10 + 33) ,
														  this->GetComponent<Transform>().GetPosition().z  ));*/
}
 