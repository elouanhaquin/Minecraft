#pragma once

#include "stdafx.h"

#include <RenderEngineAPI.h>
#include <Mesh.h>
#include <Shader.h>

namespace RenderEngineNS
{
	class RENDERENGINE_API Model
	{
	private:
		std::vector<Mesh> m_meshes{};
		std::string m_directory;

	public:
		Model() = default;
		explicit Model(const std::string& p_filePath);

		Model(const Model& p_other);
		Model(Model&& p_other) noexcept;

		Model& operator=(const Model& p_other);
		Model& operator=(Model&& p_other) noexcept;

		void Draw(Shader& p_shader) noexcept;

	private:
	//	void LoadModel(const std::string& p_filePath) noexcept;
	//	void ProcessNode(aiNode* p_node, const aiScene* p_scene) noexcept;
	//	Mesh ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene) noexcept;
	//	std::vector<Texture> LoadMaterialTextures(aiMaterial* p_mat, aiTextureType p_type,
		//std::string p_typeName) const noexcept;
	};
}