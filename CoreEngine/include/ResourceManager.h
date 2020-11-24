#pragma once

#include <Shader.h>
#include <Model.h>
#include <Texture.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	//Singleton
	class ResourceManager
	{
	public:
		static ResourceManager& Instance();

	private:
		
		ResourceManager();

		ResourceManager(ResourceManager const&) = delete;
		void operator=(ResourceManager const&) = delete;

		std::string m_modelsRootDir;
		std::string m_shaderRootDir;
		std::string m_textureRootDir;

		std::unordered_map<std::string, Model*> m_modelResources;
		std::unordered_map<std::string, Shader*> m_shaderResources;
		std::unordered_map<std::string, Texture*> m_texturesResources;


	public:
		Model * LoadModel		(const std::string&& p_name,	const std::string&& p_file,			bool p_forceReload = false);
		Shader* LoadShader		(const std::string&& p_name,	const std::string&& p_vertShader,	const std::string&& p_fragShader,	bool p_forceReload = false);
		Texture* LoadTexture	(const std::string&& p_name,	const std::string&& p_file,			const std::string&& p_type,		bool p_forceReload = false);

		Model* GetModel(const std::string&& p_name)			{ return m_modelResources.at(p_name); }
		Shader* GetShader(const std::string&& p_name)		{ return m_shaderResources.at(p_name); }
		Texture* GetTexture(const std::string&& p_name)		{ return m_texturesResources.at(p_name); }

		void FreeResources();	//Must Call this to free Resources
	};
}