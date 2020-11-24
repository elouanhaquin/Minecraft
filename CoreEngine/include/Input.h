#pragma once

#include <Camera.h>

namespace CoreEngineNS
{
	class Input
	{
	private:

		//Window
		static GLfloat m_windowWidth;
		static GLfloat m_windowHeight;
		static bool m_shouldClose;

		//Mouse
		static double m_mouseX;
		static double m_mouseY;
		static bool m_isMenu;
		static bool m_updateMouse;	//If mouse was updated during frame
		static bool m_firstMouse;
		static bool m_isClick;
		static GLfloat m_xOffset;
		static GLfloat m_yOffset;
		static GLfloat m_lastXoffset;
		static GLfloat m_lastYoffset;
		static GLfloat m_swapOffset;

		//Keyboard
		static glm::vec3 m_movementDirection;
		static int m_vertical;
		static int m_horizontal;
		static int m_depth;
		static bool m_jump;
		static bool m_sprint;
		static bool m_isCreativeMode;
		static bool m_goDown;
		static bool m_isKeyW_pressed;
		static bool m_isKeyS_pressed;
		static bool m_isKeyA_pressed;
		static bool m_isKeyD_pressed;

	public:
		Input();
		~Input();

		//OpenGL
		static void KeyCallBack(GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_mods);
		static void MouseCallBack(GLFWwindow* p_window);

		static void Click(GLFWwindow* window, int button, int action, int mods);

		static void SetWindowSize(const GLfloat& p_windowWidth, const GLfloat& p_windowHeight);
		static bool ShouldClose();
		static bool ShouldUpdateMouse();
		static float GetXOffset();
		static float GetYOffset();
		static float MouseX();
		static float MouseY();

		static void ResetXOffset();
		static void ResetYOffset();

		static glm::vec3 GetMovementDirection();
		static bool& IsMenu();

		static bool isClick();
		static bool Sprint();
		static bool Jump();
		static bool CreativeMode();
		static bool GoDown();

		static void Reset();
	};
}