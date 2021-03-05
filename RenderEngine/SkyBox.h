#pragma once
#include "RenderEngineAPI.h"
#include "stdafx.h"
#include <BlockGeometry.h>
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>
#include <atomic>

namespace RenderEngineNS
{
	class RENDERENGINE_API SkyBox
	{
		public:
			SkyBox();
			~SkyBox();

			void AddFace(int _faceType, glm::vec3 pos, uint16_t _tex);

			void AddGPUData();
			void removeGPUData();

			void Draw(Shader& p_shader, float p_time);

	private:
		int			faceCount = 0;
		unsigned int indicesCount = 0;
		bool m_isSunGoingUp = false;
		float m_buffTime = 0;
		float m_buffTimeGoUp = 0;

		std::vector<Vertex>			m_vertices;
		std::vector<GLuint>			m_indices;
		std::vector<Texture>		m_textures;

		unsigned int				m_vao, m_vbo, m_ebo;
	};

}