#include "stdafx.h"
#include <Input.h>
#include <Time.h>

using namespace CoreEngineNS;

GLfloat Input::m_windowWidth = 0;
GLfloat Input::m_windowHeight = 0;
bool Input::m_shouldClose = false;

double Input::m_mouseX = 0.0f;
double Input::m_mouseY = 0.0f;
bool Input::m_isMenu = true;
bool Input::m_updateMouse = false;
bool Input::m_firstMouse = true;
GLfloat Input::m_xOffset = 0;
GLfloat Input::m_yOffset = 0;
bool Input::m_jump = false;
bool Input::m_sprint = false;
bool Input::m_isCreativeMode = false;
bool Input::m_goDown = false;
bool Input::m_isClick = false;
GLfloat Input::m_lastXoffset = 0.0f;
GLfloat Input::m_lastYoffset = 0.0f;
GLfloat Input::m_swapOffset = 0.0f;

glm::vec3 Input::m_movementDirection = glm::vec3(0, 0, 0);
int Input::m_vertical = 0;
int Input::m_horizontal = 0;
int Input::m_depth = 0;
bool Input::m_isKeyW_pressed = false;
bool Input::m_isKeyS_pressed = false;
bool Input::m_isKeyA_pressed = false;
bool Input::m_isKeyD_pressed = false;

CoreEngineNS::Input::Input()
{
}

CoreEngineNS::Input::~Input()
{
}

void Input::KeyCallBack(GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_mods)
{
	if (p_action == GLFW_PRESS)
	{
		if (p_key == GLFW_KEY_LEFT_SHIFT)
			m_sprint = true;

		if (p_key == GLFW_KEY_SPACE)
			m_jump = true;

		if (p_key == GLFW_KEY_G)
			m_isCreativeMode = !m_isCreativeMode;

		if (p_key == GLFW_KEY_ESCAPE)
			m_shouldClose = true;

		if (p_key == GLFW_KEY_W)
		{
			m_depth = 1;
			m_isKeyW_pressed = true;
		}

		if (p_key == GLFW_KEY_S)
		{
			m_depth = -1;
			m_isKeyS_pressed = true;
		}

		if (p_key == GLFW_KEY_A)
		{
			m_horizontal = -1;
			m_isKeyA_pressed = true;
		}

		if (p_key == GLFW_KEY_D)
		{
			m_horizontal = 1;
			m_isKeyD_pressed = true;
		}

		if (m_isCreativeMode)
		{
			if (p_key == GLFW_KEY_C)
			{
				m_goDown = true;
			}
		}
	}

	if (p_action == GLFW_RELEASE)
	{
		if (p_key == GLFW_KEY_LEFT_SHIFT)
			m_sprint = false;

		if (p_key == GLFW_KEY_SPACE)
			m_jump = false;

		if (p_key == GLFW_KEY_W)
		{
			m_isKeyW_pressed = false;
			if (!m_isKeyS_pressed)
				m_depth = 0;
			else
				m_depth = -1;
		}

		if (p_key == GLFW_KEY_S)
		{
			m_isKeyS_pressed = false;
			if (!m_isKeyW_pressed)
				m_depth = 0;
			else
				m_depth = 1;
		}

		if (p_key == GLFW_KEY_A)
		{
			m_isKeyA_pressed = false;
			if (!m_isKeyD_pressed)
				m_horizontal = 0;
			else
				m_horizontal = 1;
		}

		if (p_key == GLFW_KEY_D)
		{
			m_isKeyD_pressed = false;
			if (!m_isKeyA_pressed)
				m_horizontal = 0;
			else
				m_horizontal = -1;
		}

		if (m_isCreativeMode)
		{
			if (p_key == GLFW_KEY_C)
			{
				m_goDown = false;
			}
		}
	}

	m_movementDirection = glm::vec3(m_horizontal, 0, m_depth);
	m_movementDirection.z *= -1.0f;
}

glm::vec3 Input::GetMovementDirection()
{
	return glm::vec3(m_movementDirection.x, m_movementDirection.y, m_movementDirection.z);
}

bool& CoreEngineNS::Input::IsMenu()
{
	return m_isMenu;
}

bool Input::isClick()
{
	return m_isClick;
}

void Input::Click(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
	if (p_button == GLFW_MOUSE_BUTTON_LEFT && p_action == GLFW_PRESS)
		m_isClick = true;
	else
		m_isClick = false;
}

bool Input::Sprint()
{
	return m_sprint;
}

bool Input::Jump()
{
	return m_jump;
}

bool CoreEngineNS::Input::CreativeMode()
{
	return m_isCreativeMode;
}

bool CoreEngineNS::Input::GoDown()
{
	return m_goDown;
}

void Input::Reset()
{
	m_updateMouse = false;
}

bool Input::ShouldClose()
{
	return m_shouldClose;
}

void Input::MouseCallBack(GLFWwindow* p_window)
{
	glfwGetCursorPos(p_window, &m_mouseX, &m_mouseY);

	m_updateMouse = true;

	m_xOffset = m_mouseX - m_windowWidth * 0.5f;
	m_yOffset = m_windowHeight * 0.5f - m_mouseY;

	if (m_xOffset == 0.0f && m_lastXoffset != 0.0f)
	{
		m_swapOffset = m_xOffset;
		m_xOffset = m_lastXoffset * 0.75;
		m_lastXoffset = m_swapOffset;
	}
	else
		m_lastXoffset = m_xOffset;

	if (m_yOffset == 0.0f && m_lastYoffset != 0.0f)
	{
		m_swapOffset = m_yOffset;
		m_yOffset = m_lastYoffset * 0.75;
		m_lastYoffset = m_swapOffset;
	}
	else
		m_lastYoffset = m_yOffset;

	if (!m_isMenu)
		glfwSetCursorPos(p_window, m_windowWidth * 0.5f, m_windowHeight * 0.5f);

	glfwSetMouseButtonCallback(p_window, Click);
}

bool Input::ShouldUpdateMouse()
{
	return m_updateMouse;
}

float Input::GetXOffset()
{
	return m_xOffset * TimeNS::Time::deltaTime;
}

float Input::GetYOffset()
{
	return m_yOffset * TimeNS::Time::deltaTime;
}

float Input::MouseX()
{
	return m_mouseX;
}

float Input::MouseY()
{
	return m_mouseY;
}

void Input::ResetXOffset()
{
	m_xOffset = 0.0f;
}

void Input::ResetYOffset()
{
	m_yOffset = 0.0f;
}

void Input::SetWindowSize(const GLfloat& p_windowWidth, const GLfloat& p_windowHeight)
{
	m_windowWidth = p_windowWidth;
	m_windowHeight = p_windowHeight;
}