#pragma once

#include "stdafx.h"
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>
#include <atomic>

#include "RenderEngineAPI.h"

namespace RenderEngineNS
{
	class RENDERENGINE_API ChunkMesh
	{
	public:

		ChunkMesh();
		~ChunkMesh();

		void AddFace(int _faceType, glm::vec3 pos);

		void AddGPUData();
		void removeGPUData();

		void Draw(Shader& p_shader);

		

	private:

		int			faceCount		= 0;
		unsigned int indicesCount	= 0;

		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Texture>		m_textures;

		unsigned int				m_vao, m_vbo, m_ebo;

	};
}