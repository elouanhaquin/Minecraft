#pragma once

#include <RenderEngineAPI.h>
#include <Window.h>
#include <Model.h>
#include <Camera.h>

namespace RenderEngineNS
{
	class RENDERENGINE_API RenderEngine
	{
	private:
		std::shared_ptr<Window> m_window;
		int m_width;
		int m_height;

	public:
		RenderEngine();
		~RenderEngine();

		Camera* m_camera;

		void SetupWindow(const int& p_width, const int& p_height, bool isFullscreen = false);
		void UpdateCamera(const glm::vec3& p_playerPosition, float p_xoffset, float p_yoffset, glm::vec3 p_playerMovement, bool p_isOnTheFloor, bool p_isSprint, bool p_isCreativeMode);
		Camera* GetCamera() { return m_camera; }
		void Render(Model* p_model, Shader* p_shader, const glm::vec3& p_position) const;
		Model* LoadModel(const std::string& p_filePath);
		Shader* LoadShader(const std::string& p_vertexShader, const std::string& p_fragmentShader);

		void BeginFrame();
		void EndFrame();

		std::shared_ptr<Window> GetWindow();
		int WindowWidth() const;
		int WindowHeight() const;
	};
}
