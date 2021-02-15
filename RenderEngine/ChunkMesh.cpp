#include "stdafx.h"
#include <ChunkMesh.h>


using namespace RenderEngineNS;

ChunkMesh::ChunkMesh()
{
	indicesCount	= 0;
	faceCount		= 0;
	m_textures.push_back(Texture(4, "Dirt"));
}

ChunkMesh::~ChunkMesh()
{
	m_indices.clear();
	m_vertices.clear();
	m_textures.clear();
	faceCount = 0;
}

void ChunkMesh::AddGPUData()
{
	indicesCount = m_indices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
		
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_normal)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_textureCoord)));

	//glBindVertexArray(0);
}

void RenderEngineNS::ChunkMesh::removeGPUData()
{
	m_indices.clear();
	m_vertices.clear();
	indicesCount = 0;


	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

	glUnmapBuffer(m_vbo);
	glUnmapBuffer(m_vao);
	glUnmapBuffer(m_ebo);

}

void ChunkMesh::AddFace(int _faceType, glm::vec3 pos)
{
	++faceCount;
	Vertex v[6];

	switch (_faceType)
	{
	case 0: //Top

		v[0].m_position = glm::vec3(0.5f, 0.5f, -0.5f)	+ pos;
		v[1].m_position = glm::vec3(-0.5f, 0.5f, 0.5f)	+ pos;
		v[2].m_position = glm::vec3(0.5f, 0.5f, 0.5f)	+ pos;

		v[3].m_position = glm::vec3(0.5f, 0.5f, -0.5f)	+ pos;
		v[4].m_position = glm::vec3(-0.5f, 0.5f, -0.5f)	+ pos;
		v[5].m_position = glm::vec3(-0.5f, 0.5f, 0.5f)	+ pos;

		//TextCoords
		v[0].m_textureCoord = glm::vec2(0.33, 0);
		v[1].m_textureCoord = glm::vec2(0, 0.33);
		v[2].m_textureCoord = glm::vec2(0.33, 0.33);

		v[3].m_textureCoord = glm::vec2(0.33, 0);
		v[4].m_textureCoord = glm::vec2(0, 0);
		v[5].m_textureCoord = glm::vec2(0, 0.33);

		//Normals
		v[0].m_normal = glm::vec3(0, -0.99, 0);
		v[1].m_normal = glm::vec3(0, -0.99, 0);
		v[2].m_normal = glm::vec3(0, -0.99, 0);

		v[3].m_normal = glm::vec3(0, -0.99, 0);
		v[4].m_normal = glm::vec3(0, -0.99, 0);
		v[5].m_normal = glm::vec3(0, -0.99, 0);


		m_indices.insert(m_indices.end(),
			{
				indicesCount,
				indicesCount + 1,
				indicesCount + 2,
				indicesCount + 2,
				indicesCount + 3,
				indicesCount
			});
		indicesCount += 4;

		for (int i = 0; i < 6; ++i)
		{
			m_vertices.push_back(v[i]);
		}

		break;
	case 1: //Bottom

		v[0].m_position = glm::vec3(-0.5f, -0.5f, -0.5f) + pos;
		v[1].m_position = glm::vec3(0.5f, -0.5f, 0.5f) + pos;
		v[2].m_position = glm::vec3(-0.5f, -0.5f, 0.5f) + pos;

		v[3].m_position = glm::vec3(-0.5f, -0.5f, -0.5f) + pos;
		v[4].m_position = glm::vec3(0.5f, -0.5f, -0.5f) + pos;
		v[5].m_position = glm::vec3(0.5f, -0.5f, 0.5f) + pos;

		//TextCoords
		v[0].m_textureCoord = glm::vec2(1, 0.65);
		v[1].m_textureCoord = glm::vec2(0.65, 1);
		v[2].m_textureCoord = glm::vec2(1, 1);

		v[3].m_textureCoord = glm::vec2(1, 0.65);
		v[4].m_textureCoord = glm::vec2(0.65, 0.65);
		v[5].m_textureCoord = glm::vec2(0.65, 1);

		//Normals
		v[0].m_normal = glm::vec3(0, -0.1, 0);
		v[1].m_normal = glm::vec3(0, -0.1, 0);
		v[2].m_normal = glm::vec3(0, -0.1, 0);

		v[3].m_normal = glm::vec3(0, -0.1, 0);
		v[4].m_normal = glm::vec3(0, -0.1, 0);
		v[5].m_normal = glm::vec3(0, -0.1, 0);

		m_indices.insert(m_indices.end(),
			{
				indicesCount,
				indicesCount + 1,
				indicesCount + 2,
				indicesCount + 2,
				indicesCount + 3,
				indicesCount
			});
		indicesCount += 4;

		for (int i = 0; i < 6; ++i)
		{
			m_vertices.push_back(v[i]);
		}

		break;
	case 2: //Front

		v[0].m_position = glm::vec3(0.5f, 0.5f, 0.5f) + pos;
		v[1].m_position = glm::vec3(-0.5f, -0.5f, 0.5f) + pos;
		v[2].m_position = glm::vec3(0.5f, -0.5f, 0.5f) + pos;

		v[3].m_position = glm::vec3(0.5f, 0.5f, 0.5f) + pos;
		v[4].m_position = glm::vec3(-0.5f, 0.5f, 0.5f) + pos;
		v[5].m_position = glm::vec3(-0.5f, -0.5f, 0.5f) + pos;

		//TextCoords
		v[0].m_textureCoord = glm::vec2(0.66, 1);
		v[1].m_textureCoord = glm::vec2(0.35, 0);
		v[2].m_textureCoord = glm::vec2(0.66, 0);

		v[3].m_textureCoord = glm::vec2(0.66, 1);
		v[4].m_textureCoord = glm::vec2(0.35, 1);
		v[5].m_textureCoord = glm::vec2(0.35, 0);

		//Normals
		v[0].m_normal = glm::vec3(0, 0, -0.90);
		v[1].m_normal = glm::vec3(0, 0, -0.90);
		v[2].m_normal = glm::vec3(0, 0, -0.90);

		v[3].m_normal = glm::vec3(0, 0, -0.90);
		v[4].m_normal = glm::vec3(0, 0, -0.90);
		v[5].m_normal = glm::vec3(0, 0, -0.90);

		m_indices.insert(m_indices.end(),
			{
				indicesCount,
				indicesCount + 1,
				indicesCount + 2,
				indicesCount + 2,
				indicesCount + 3,
				indicesCount
			});
		indicesCount += 4;

		for (int i = 0; i < 6; ++i)
		{
			m_vertices.push_back(v[i]);
		}

		break;
	case 3: //Back

		v[0].m_position = glm::vec3(-0.5f, 0.5f, -0.5f) + pos;
		v[1].m_position = glm::vec3(0.5f, -0.5f, -0.5f) + pos;
		v[2].m_position = glm::vec3(-0.5f, -0.5f, -0.5f) + pos;

		v[3].m_position = glm::vec3(-0.5f, 0.5f, -0.5f) + pos;
		v[4].m_position = glm::vec3(0.5f, 0.5f, -0.5f) + pos;
		v[5].m_position = glm::vec3(0.5f, -0.5f, -0.5f) + pos;

		//TextCoords
		v[0].m_textureCoord = glm::vec2(0.66, 1);
		v[1].m_textureCoord = glm::vec2(0.35, 0);
		v[2].m_textureCoord = glm::vec2(0.66, 0);

		v[3].m_textureCoord = glm::vec2(0.66, 1);
		v[4].m_textureCoord = glm::vec2(0.35, 1);
		v[5].m_textureCoord = glm::vec2(0.35, 0);


		//Normals
		v[0].m_normal = glm::vec3(0, 0, -0.95);
		v[1].m_normal = glm::vec3(0, 0, -0.95);
		v[2].m_normal = glm::vec3(0, 0, -0.95);

		v[3].m_normal = glm::vec3(0, 0, -0.95);
		v[4].m_normal = glm::vec3(0, 0, -0.95);
		v[5].m_normal = glm::vec3(0, 0, -0.95);

		m_indices.insert(m_indices.end(),
			{
				indicesCount,
				indicesCount + 1,
				indicesCount + 2,
				indicesCount + 2,
				indicesCount + 3,
				indicesCount
			});
		indicesCount += 4;

		for (int i = 0; i < 6; ++i)
		{
			m_vertices.push_back(v[i]);
		}

		break;
	case 4: //Right

		v[0].m_position = glm::vec3(0.5f, 0.5f, -0.5f) + pos;
		v[1].m_position = glm::vec3(0.5f, -0.5f, 0.5f) + pos;
		v[2].m_position = glm::vec3(0.5f, -0.5f, -0.5f) + pos;

		v[3].m_position = glm::vec3(0.5f, 0.5f, -0.5f) + pos;
		v[4].m_position = glm::vec3(0.5f, 0.5f, 0.5f) + pos;
		v[5].m_position = glm::vec3(0.5f, -0.5f, 0.5f) + pos;

		//TextCoords
		v[0].m_textureCoord = glm::vec2(0.66, 1);
		v[1].m_textureCoord = glm::vec2(0.35, 0);
		v[2].m_textureCoord = glm::vec2(0.66, 0);

		v[3].m_textureCoord = glm::vec2(0.66, 1);
		v[4].m_textureCoord = glm::vec2(0.35, 1);
		v[5].m_textureCoord = glm::vec2(0.35, 0);


		//Normals
		v[0].m_normal = glm::vec3(-0.98, 0, 0);
		v[1].m_normal = glm::vec3(-0.98, 0, 0);
		v[2].m_normal = glm::vec3(-0.98, 0, 0);

		v[3].m_normal = glm::vec3(-0.98, 0, 0);
		v[4].m_normal = glm::vec3(-0.98, 0, 0);
		v[5].m_normal = glm::vec3(-0.98, 0, 0);

		m_indices.insert(m_indices.end(),
			{
				indicesCount,
				indicesCount + 1,
				indicesCount + 2,
				indicesCount + 2,
				indicesCount + 3,
				indicesCount
			});
		indicesCount += 4;

		for (int i = 0; i < 6; ++i)
		{
			m_vertices.push_back(v[i]);
		}

		break;
	case 5: //Left

		v[0].m_position = glm::vec3(-0.5f, 0.5f, 0.5f) + pos;
		v[1].m_position = glm::vec3(-0.5f, -0.5f, -0.5f) + pos;
		v[2].m_position = glm::vec3(-0.5f, -0.5f, 0.5f) + pos;

		v[3].m_position = glm::vec3(-0.5f, 0.5f, 0.5f) + pos;
		v[4].m_position = glm::vec3(-0.5f, 0.5f, -0.5f) + pos;
		v[5].m_position = glm::vec3(-0.5f, -0.5f, -0.5f) + pos;

		//TextCoords
		v[0].m_textureCoord = glm::vec2(0.66, 1);
		v[1].m_textureCoord = glm::vec2(0.35, 0);
		v[2].m_textureCoord = glm::vec2(0.66, 0);

		v[3].m_textureCoord = glm::vec2(0.66, 1);
		v[4].m_textureCoord = glm::vec2(0.35, 1);
		v[5].m_textureCoord = glm::vec2(0.35, 0);


		//Normals
		v[0].m_normal = glm::vec3(-0.92, 0, 0);
		v[1].m_normal = glm::vec3(-0.92, 0, 0);
		v[2].m_normal = glm::vec3(-0.92, 0, 0);

		v[3].m_normal = glm::vec3(-0.92, 0, 0);
		v[4].m_normal = glm::vec3(-0.92, 0, 0);
		v[5].m_normal = glm::vec3(-0.92, 0, 0);

		m_indices.insert(m_indices.end(),
			{
				indicesCount,
				indicesCount + 1,
				indicesCount + 2,
				indicesCount + 2,
				indicesCount + 3,
				indicesCount
			});
		indicesCount += 4;

		for (int i = 0; i < 6; ++i)
		{
			m_vertices.push_back(v[i]);
		}

		break;
	}
}

void ChunkMesh::Draw(Shader& p_shader)
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

										  // retrieve texture number (the N in diffuse_textureN)
		std::string number;
		const std::string name = m_textures[i].m_type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

												 // now set the sampler to the correct texture unit
												 glUniform1i(glGetUniformLocation(p_shader.GetRendererID(), (name + number).c_str()), i);
		
		

		glm::vec3 light = glm::vec3(-4, -10, 0);
		p_shader.SetVec3("lightPos", light);

		p_shader.SetUniform1i(name + number, i);
		// and finally bind the texture
		 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glBindTexture(GL_TEXTURE_2D, m_textures[i].m_id);

	}
	// draw mesh
	glBindVertexArray(m_vao);

	//glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, m_indices[0], m_indices.size());
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
