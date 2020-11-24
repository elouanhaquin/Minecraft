#include "stdafx.h"

#include <ResourceManager.h>

using namespace CoreEngineNS;

ResourceManager& ResourceManager::Instance()
{
	static ResourceManager instance;
	return instance;
}


ResourceManager::ResourceManager() : m_modelsRootDir {"res/meshes/"}, m_shaderRootDir {"res/shaders/"}, m_textureRootDir{"res/textures/"}
{
}

void ResourceManager::FreeResources()
{
	for (auto& modelPair : m_modelResources)
		delete modelPair.second;


	for (auto& shaderPair : m_shaderResources)
		delete shaderPair.second;

	for (auto& texturePair : m_texturesResources)
		delete texturePair.second;
}

Model* ResourceManager::LoadModel(const std::string && p_name, const std::string && p_file, bool p_forceReload)
{
	if (p_name == "Button")
	{
		auto res = m_modelResources.emplace(p_name, new Model(p_name));
		return res.first->second;
	}
	
	if (!p_forceReload && m_modelResources.find(p_name) != m_modelResources.end())
	{
		std::cout << "ERROR : UNABLE TO FIND RESSOURCE FOR " + p_name  << std::endl;
		return m_modelResources[p_name];
	}
		

	/*Model* model = new Model(m_modelsRootDir + p_file);
	m_modelResources.emplace(p_name, model);
	return model;*/
	auto res = m_modelResources.emplace(p_name, new Model(m_modelsRootDir + p_file));
	return res.first->second;
}

Shader* ResourceManager::LoadShader(const std::string&& p_name, const std::string&& p_vertShader, const std::string&& p_fragShader, bool p_forceReload)
{
	if (!p_forceReload && m_shaderResources.find(p_name) != m_shaderResources.end())
		return m_shaderResources[p_name];

	auto res = m_shaderResources.emplace(p_name, new Shader(m_shaderRootDir + p_vertShader, m_shaderRootDir + p_fragShader));
	return res.first->second;
}

Texture* ResourceManager::LoadTexture(const std::string&& p_name, const std::string&& p_file, const std::string&& p_type, bool p_forceReload)
{
	if (!p_forceReload && m_texturesResources.find(p_name) != m_texturesResources.end())
		return m_texturesResources[p_name];

	auto res = m_texturesResources.emplace(p_name, new Texture(TextureFromFile(p_file.c_str(), m_textureRootDir), p_type));
	return res.first->second;
}