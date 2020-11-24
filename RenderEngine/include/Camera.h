#pragma once
#include "stdafx.h"

#include "RenderEngineAPI.h"

namespace RenderEngineNS
{
	enum Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 12.0f;
	const float ZOOM = 45.0f;

	// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
	class RENDERENGINE_API Camera
	{
	private:
		// Camera Attributes
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

		// Camera Effect
		float m_walkMovemantY;
		int m_upDownY;
		float m_walkMovemantX;
		int m_upDownX;

		// Euler Angles
		float m_yaw;
		float m_pitch;

		// Camera options
		float m_movementSpeed;
		float m_mouseSensitivity;
		float m_zoom;

	public:
		// Constructor with vectors
		explicit Camera(const glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f),
			const float p_yaw = YAW,
			const float p_pitch = PITCH);

		// Constructor with scalar values
		Camera(const float p_posX, const float p_posY, const float p_posZ,
			const float p_upX, const float p_upY, const float p_upZ,
			const float p_yaw, const float p_pitch);

		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix() const;

		// Make the current position child of the player
		void UpdatePosition(const glm::vec3 p_PlayerPosition, glm::vec3 p_playerMovement, bool p_isJumping, bool p_isSprint, bool p_isCreativeMode);

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement p_direction, float p_deltaTime);

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float p_xoffset, float p_yoffset, GLboolean p_constrainPitch = true);

		// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessZoom(bool p_isSprint, bool p_isCreativeMode, glm::vec3 p_playerMovement);


		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& p_position) { m_position = p_position; }
		const glm::vec3& GetFront() const { return m_front; }
		void SetFront(const glm::vec3& p_front) { m_front = p_front; }
		const glm::vec3& GetUp() const { return m_up; }
		void SetUp(const glm::vec3& p_up) { m_up = p_up; }
		const glm::vec3& GetRight() const { return m_right; }
		void SetRight(const glm::vec3& p_right) { m_right = p_right; }
		const glm::vec3& GetWorldUp() const { return m_worldUp; }
		void SetWorldUp(const glm::vec3& p_worldUp) { m_worldUp = p_worldUp; }
		float GetYaw() const { return m_yaw; }
		void SetYaw(const float p_yaw) { m_yaw = p_yaw; }
		float GetPitch() const { return m_pitch; }
		void SetPitch(const float p_pitch) { m_pitch = p_pitch; }
		float GetMovementSpeed() const { return m_movementSpeed; }
		void SetMovementSpeed(const float p_movementSpeed) { m_movementSpeed = p_movementSpeed; }
		float GetMouseSensitivity() const { return m_mouseSensitivity; }
		void SetMouseSensitivity(const float p_mouseSensitivity) { m_mouseSensitivity = p_mouseSensitivity; }
		float GetZoom() const { return m_zoom; }
		void SetZoom(const float p_zoom) { m_zoom = p_zoom; }


	private:
		// Calculates the front vector from the Camera's (updated) Euler Angles
		void UpdateCameraVectors();
	};

}
