#pragma once

#include "RenderEngineAPI.h"
#include <Texture.h>
#include <Shader.h>

namespace RenderEngineNS
{
	class RENDERENGINE_API PostProcessing
	{
	public:
		PostProcessing();
		~PostProcessing();

		void createDepthTexture();
		void attachDepthTexture();

		void draw(Shader& p_shader, float p_time);
		void renderScene( Shader &p_shader);
		void renderQuad();

	private:
		
		unsigned int m_vao ,m_vbo,  m_fbo , m_depthMap ;
		const unsigned int SHADOW_WIDTH = 1280, SHADOW_HEIGHT = 720;
	};
}
