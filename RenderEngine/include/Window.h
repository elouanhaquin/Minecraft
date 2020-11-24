#pragma once

#include "RenderEngineAPI.h"

namespace RenderEngineNS
{
	class RENDERENGINE_API Window
	{
	private:
		GLint m_width;
		GLint m_height;
		GLFWwindow* m_window;


	public:
		Window(const GLint& p_width, const GLint& p_height);
		~Window();

		bool Setup(bool isFullScreen);
		GLFWwindow* WindowGLFW();

	};
}
