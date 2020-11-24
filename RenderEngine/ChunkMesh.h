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

		void AddFace(int _faceType, glm::vec3 pos);

		void AddGPUData();

		void Draw(Shader& p_shader);

		~ChunkMesh();

	private:

		int			faceCount		= 0;
		unsigned int indicesCount	= 0;

		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;

		unsigned int				m_vao, m_vbo, m_ebo;

	};
}