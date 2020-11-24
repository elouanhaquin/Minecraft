#include "stdafx.h"

#include <Camera.h>

using namespace RenderEngineNS;

Camera::Camera(
	const glm::vec3 p_position,
	const glm::vec3 p_up,
	const float p_yaw,
	const float p_pitch
) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED),
m_mouseSensitivity(SENSITIVITY),
m_zoom(ZOOM)
{
	m_position = p_position;
	m_worldUp = p_up;
	m_yaw = p_yaw;
	m_pitch = p_pitch;
	m_walkMovemantY = 0.0f;
	m_upDownY = 1;
	m_walkMovemantX = 0.0f;
	m_upDownX = 1;
	UpdateCameraVectors();
}

Camera::Camera(
	const float p_posX, const float p_posY, const float p_posZ,
	const float p_upX, const float p_upY, const float p_upZ,
	const float p_yaw, const float p_pitch
) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
m_movementSpeed(SPEED),
m_mouseSensitivity(SENSITIVITY),
m_zoom(ZOOM)
{
	m_position = glm::vec3(p_posX, p_posY, p_posZ);
	m_worldUp = glm::vec3(p_upX, p_upY, p_upZ);
	m_yaw = p_yaw;
	m_pitch = p_pitch;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

float timerCountY = 0.0f;
float timerCountX = 0.0f;
float walkTime = 0.0f;
float timeAtWalkStart = 0.0f;
bool isWalkStart = false;
void Camera::UpdatePosition(const glm::vec3 p_playerPosition, glm::vec3 p_playerMovement, bool p_isOnTheFloor, bool p_isSprint, bool p_isCreativeMode)
{
	m_position = p_playerPosition;

	if (p_isOnTheFloor)
	{
		if (p_playerMovement.z != 0 && !p_isCreativeMode
			|| p_playerMovement.x != 0 && !p_isCreativeMode)
		{
			if (!isWalkStart)
			{
				timeAtWalkStart = glfwGetTime();
				isWalkStart = true;
			}

			if (m_upDownY == 1)
			{
				walkTime = glfwGetTime() - timeAtWalkStart;
				if (walkTime - timerCountY >= 1.0f / 60.0f)
				{
					m_walkMovemantY += p_isSprint && p_playerMovement.z < 0 ?
						0.05f * (1.0f + ((walkTime - timerCountY) / (1.0f / 60.0f) - 0.5f)) : 0.025f * (1.0f + ((walkTime - timerCountY) / (1.0f / 60.0f) - 0.5f));
					timerCountY = walkTime;
				}
				if (m_walkMovemantY >= 0.25f)
				{
					m_walkMovemantY = 0.25f;
					m_upDownY = 0;
				}
			}
			else
			{
				walkTime = glfwGetTime() - timeAtWalkStart;
				if (walkTime - timerCountY >= 1.0f / 60.0f)
				{
					m_walkMovemantY -= p_isSprint && p_playerMovement.z < 0 ?
						0.05f * (1.0f + ((walkTime - timerCountY) / (1.0f / 60.0f) - 0.5f)) : 0.025f * (1.0f + ((walkTime - timerCountY) / (1.0f / 60.0f) - 0.5f));
					timerCountY = walkTime;
				}
				if (m_walkMovemantY <= -0.25f)
				{
					m_walkMovemantY = -0.25f;
					m_upDownY = 1;
				}
			}
			m_position.y += glm::sin(m_walkMovemantY) * 1.0f; // use of sinus useless but why not

			if (m_upDownX == 1)
			{
				walkTime = glfwGetTime() - timeAtWalkStart;
				if (walkTime - timerCountX >= 1.0f / 60.0f)
				{
					m_walkMovemantX += p_isSprint && p_playerMovement.z < 0 ?
						0.025f * (1.0f + ((walkTime - timerCountX) / (1.0f / 60.0f) - 0.5f)) : 0.0125f * (1.0f + ((walkTime - timerCountX) / (1.0f / 60.0f) - 0.5f));
					timerCountX = walkTime;
				}
				if (m_walkMovemantX >= 0.25f)
				{
					m_walkMovemantX = 0.25f;
					m_upDownX = 0;
				}
			}
			else
			{
				walkTime = glfwGetTime() - timeAtWalkStart;
				if (walkTime - timerCountX >= 1.0f / 60.0f)
				{
					m_walkMovemantX -= p_isSprint && p_playerMovement.z < 0 ?
						0.025f * (1.0f + ((walkTime - timerCountX) / (1.0f / 60.0f) - 0.5f)) : 0.0125f * (1.0f + ((walkTime - timerCountX) / (1.0f / 60.0f) - 0.5f));
					timerCountX = walkTime;
				}
				if (m_walkMovemantX <= -0.25f)
				{
					m_walkMovemantX = -0.25f;
					m_upDownX = 1;
				}
			}
			if (p_playerMovement.z != 0)
			{
				m_position.x += glm::sin(m_walkMovemantX) * 1.0f;
			}
		}
		else
		{
			m_walkMovemantY = 0.0f;
			m_walkMovemantX = 0.0f;
			timerCountX = 0.0f;
			timerCountY = 0.0f;
			walkTime = 0.0f;
			timeAtWalkStart = 0.0f;
			isWalkStart = false;
		}
	}
	else
	{
		m_walkMovemantY = 0.0f;
		m_walkMovemantX = 0.0f;
		timerCountX = 0.0f;
		timerCountY = 0.0f;
		walkTime = 0.0f;
		timeAtWalkStart = 0.0f;
		isWalkStart = false;
	}
}


void Camera::ProcessKeyboard(const Camera_Movement p_direction, const float p_deltaTime)
{
	const float velocity = m_movementSpeed * p_deltaTime;
	if (p_direction == FORWARD)
		m_position += m_front * velocity;
	if (p_direction == BACKWARD)
		m_position -= m_front * velocity;
	if (p_direction == LEFT)
		m_position -= m_right * velocity;
	if (p_direction == RIGHT)
		m_position += m_right * velocity;
}

void Camera::ProcessMouseMovement(float p_xoffset, float p_yoffset, const GLboolean p_constrainPitch)
{
	p_xoffset *= m_mouseSensitivity /** (1.0f + p_deltaTime)*/;
	p_yoffset *= m_mouseSensitivity /** (1.0f + p_deltaTime)*/;

	m_yaw += p_xoffset;
	m_pitch += p_yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (p_constrainPitch)
	{
		m_pitch = m_pitch > 89.0f ? 89.0f : m_pitch < -89.0f ? -89.0f : m_pitch;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessZoom(bool p_isSprint, bool p_isCreativeMode, glm::vec3 p_playerMovement)
{
	if (p_isSprint)
	{
		if (p_playerMovement.z < 0)
		{
			m_zoom += 1.0f;
			if (m_zoom >= 50.0f)
				m_zoom = 50.0f;
		}
		else if (p_isCreativeMode && p_playerMovement.z != 0)
		{
			m_zoom += 1.0f;
			if (m_zoom >= 50.0f)
				m_zoom = 50.0f;
		}
		else
			m_zoom = 45.0f;
	}
	else
		m_zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));

	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::normalize(glm::cross(m_right, m_front));
}