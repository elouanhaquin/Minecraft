#pragma once

#include "stdafx.h"
#include <BlockGeometry.h>
#include <Time.h>
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

		void Draw(Shader& p_shader,float p_dayTime, float p_time);
		
	private:

		int			faceCount = 0;
		unsigned int indicesCount = 0;

		std::vector<Vertex>			m_vertices;
		std::vector<Vertex>			m_RenderVertices;
		std::vector<GLuint>			m_indices;
		std::vector<Texture>		m_textures;

		unsigned int				m_vao, m_vbo, m_ebo, m_fbo, m_depthMap; // here fbo is my depth map

	public:

		const unsigned int SHADOW_WIDTH = 1280, SHADOW_HEIGHT = 720;
	};
}