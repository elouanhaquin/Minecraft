#pragma once

#include "stdafx.h"
#include <BlockGeometry.h>
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>
#include <atomic>

#include "RenderEngineAPI.h"

namespace RenderEngineNS
{
	class RENDERENGINE_API DecorationMesh
	{

	public:
		DecorationMesh();
		~DecorationMesh();

		void AddFace(int _faceType, glm::vec3 pos, uint16_t _tex);

		void AddGPUData();
		void removeGPUData();

		void Draw(Shader& p_shader);
		
	private:

		int			faceCount = 0;
		unsigned int indicesCount = 0;
		int time = 1000;

		std::vector<Vertex>			m_vertices;
		std::vector<GLuint>			m_indices;
		std::vector<Texture>		m_textures;

		unsigned int				m_vao, m_vbo, m_ebo;
	};
}