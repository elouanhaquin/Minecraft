#pragma once

#include "stdafx.h"
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>
#include <atomic>

#include "RenderEngineAPI.h"

namespace RenderEngineNS
{
	class RENDERENGINE_API BlockGeometry
	{
	private: 
		unsigned int indicesCount;

		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Texture>		    m_textures;

	public:
		BlockGeometry();
		~BlockGeometry();	

		 void setBlockGeometry(int _faceType, glm::vec3 pos);

		 std::vector<Vertex> getVertices()		{ return m_vertices; }
		 std::vector<unsigned int> getIndices()   { return m_indices;  }
		 std::vector<Texture> getTextures()		{ return m_textures; }

	};
}