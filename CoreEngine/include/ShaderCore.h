#pragma once

#include <Component.h>
#include <Shader.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class ShaderCore : public Component
	{
	private:
		Shader* m_shader;

	public:
		ShaderCore();
		~ShaderCore();

		void SetShader(Shader* p_shader);
		Shader* GetShader();
	};
}