#pragma once

#include "stdafx.h"

#include <Shader.h>
#include <Model.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	//TODO
	//Singleton
	class ResManager
	{
	private:
		std::string m_modelsRootDir;
		std::string m_shaderRootDir;
		std::string m_textureRootDir;

		std::unordered_map<std::string, Model*> m_modelResources;
		std::unordered_map<std::string, Shader*> m_shaderResources;

	public:
		ResManager();
		~ResManager();

		Model* LoadModel(const std::string&& p_name, const std::string&& p_file, bool p_forceReload = false);
		Shader* LoadShader(const std::string&& p_name, const std::string&& p_vertShader, const std::string&& p_fragShader, bool p_forceReload = false);

		Model* GetModel(const std::string&& p_name) { return m_modelResources.at(p_name); }
		Shader* GetShader(const std::string&& p_name) { return m_shaderResources.at(p_name); }
	};
}