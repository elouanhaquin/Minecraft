#pragma once

#include "stdafx.h"
#include <RenderEngineAPI.h>

namespace RenderEngineNS
{
	class RENDERENGINE_API Shader
	{
	private:
		std::string m_filePathVertex;
		std::string m_filePathFragment;
		unsigned int m_rendererID;

		std::unordered_map<std::string, int> m_uniformLocationCache;

	public:
		Shader() = default;
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetVec3(const std::string& name, glm::vec3& p_vec);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& p_name, const glm::mat4& p_mat);

		inline unsigned int GetRendererID() const { return m_rendererID; }

	private:
		int GetUniformLocation(const std::string& name);
		std::string Parse(const std::string& filePath) const;
		int Compile(unsigned, const std::string& source) const;
	};
}