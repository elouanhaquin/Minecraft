#include "stdafx.h"

#include <ResManager.h>

using namespace CoreEngineNS;

ResManager::ResManager(): m_modelsRootDir {"res/meshes/"}, m_shaderRootDir {"res/shaders/"}
{
}

ResManager::~ResManager()
{
	m_modelResources.clear();
	m_shaderResources.clear();
}

Model* ResManager::LoadModel(const std::string && p_name, const std::string && p_file, bool p_forceReload)
{
	if (!p_forceReload && m_modelResources.find(p_name) != m_modelResources.end())
		return m_modelResources[p_name];

	auto res = m_modelResources.emplace(p_name, new Model(m_modelsRootDir + p_file));
	return res.first->second;
}

Shader* ResManager::LoadShader(const std::string&& p_name, const std::string&& p_vertShader, const std::string&& p_fragShader, bool p_forceReload)
{
	if (!p_forceReload && m_shaderResources.find(p_name) != m_shaderResources.end())
		return m_shaderResources[p_name];

	auto res = m_shaderResources.emplace(p_name, new Shader(m_shaderRootDir + p_vertShader, m_shaderRootDir + p_fragShader));
	return res.first->second;
}
