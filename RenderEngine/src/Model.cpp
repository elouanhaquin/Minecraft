#include "stdafx.h"

#include <Model.h>

using namespace RenderEngineNS;

Model::Model(const std::string& p_filePath)
{


//	LoadModel(p_filePath);
}
//m_renderEngine->Render(m_model, gameObject->GetComponent<MeshRenderer>().GetMesh, gameObject->GetComponent<Transform>().GetPosition);


Model::Model(const Model& p_other) : m_meshes(p_other.m_meshes),
m_directory(p_other.m_directory){}

Model::Model(Model&& p_other) noexcept : m_meshes(std::move(p_other.m_meshes)),
m_directory(std::move(p_other.m_directory)) {}

Model& Model::operator=(const Model& p_other)
{
	if (this == &p_other)
		return *this;
	m_meshes = p_other.m_meshes;
	m_directory = p_other.m_directory;
	return *this;
}

Model& Model::operator=(Model&& p_other) noexcept
{
	if (this == &p_other)
		return *this;
	m_meshes = std::move(p_other.m_meshes);
	m_directory = std::move(p_other.m_directory);
	return *this;
}

void Model::Draw(Shader& p_shader) noexcept
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].Draw(p_shader);
}

/*void Model::LoadModel(const std::string& p_filePath) noexcept
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(p_filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
		return;
	}
	m_directory = p_filePath.substr(0, p_filePath.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* p_node, const aiScene* p_scene) noexcept
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < p_node->mNumMeshes; i++)
	{
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
		Mesh meshObj = ProcessMesh(mesh, p_scene);;
		meshObj.Unbind();
		m_meshes.push_back(meshObj);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < p_node->mNumChildren; i++)
	{
		ProcessNode(p_node->mChildren[i], p_scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene) noexcept
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < p_mesh->mNumVertices; i++)
	{
		Vertex vertex{};

		// process vertex positions, normals and texture coordinates

		// Positions
		vertex.m_position.x = p_mesh->mVertices[i].x;
		vertex.m_position.y = p_mesh->mVertices[i].y;
		vertex.m_position.z = p_mesh->mVertices[i].z;

		// Normals
		if (p_mesh->mNormals)
		{
			vertex.m_normal.x = p_mesh->mNormals[i].x;
			vertex.m_normal.y = p_mesh->mNormals[i].y;
			vertex.m_normal.z = p_mesh->mNormals[i].z;
		}
		else
		{
			vertex.m_normal.x = 0;
			vertex.m_normal.y = 0;
			vertex.m_normal.z = 0;
		}

		// Text coords
		if (p_mesh->mTextureCoords[0])
		{
			vertex.m_textureCoord.x = p_mesh->mTextureCoords[0][i].x;
			vertex.m_textureCoord.y = p_mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.m_textureCoord.x = 0.0f;
			vertex.m_textureCoord.y = 0.0f;
		}

		vertices.push_back(vertex);
	}

	// process indices
	for (unsigned int i = 0; i < p_mesh->mNumFaces; i++)
	{
		const aiFace face = p_mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process material
	if (p_mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = p_scene->mMaterials[p_mesh->mMaterialIndex];

		// 1. diffuse maps
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// 2. normal maps
		std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* p_mat,
	const aiTextureType p_type,
	const std::string p_typeName) const noexcept
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < p_mat->GetTextureCount(p_type); i++)
	{
		aiString str;
		p_mat->GetTexture(p_type, i, &str);
		textures.emplace_back(TextureFromFile(str.C_Str(), m_directory), p_typeName, str);
	}

	return textures;
}*/