#pragma once

#include "stdafx.h"
#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>

namespace RenderEngineNS
{
	class Mesh
	{
	private:
		// OPENGL BUFFERS
		unsigned int				m_vao, m_vbo, m_ebo;

		// MESH DATA
		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Texture>		m_textures;

	public:
		Mesh() = default;
		Mesh(std::string p_Type);
		explicit Mesh(const std::vector<Vertex>& p_vertices, const std::vector<unsigned int>& p_indices, const std::vector<Texture>& p_textures);
		~Mesh()		= default;

		void Setup();
		void SetupTerrain();
		void Draw(Shader& p_shader);

		void DrawInstanced(Shader& p_shader, int size);

		void Bind() const;
		void Unbind() const;
	};
}