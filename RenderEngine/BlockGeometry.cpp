#include "stdafx.h"
#include "BlockGeometry.h"

RenderEngineNS::BlockGeometry::BlockGeometry()
{
	indicesCount = 0;
}

RenderEngineNS::BlockGeometry::~BlockGeometry()
{
}

void RenderEngineNS::BlockGeometry::setBlockGeometry(int _faceType, glm::vec3 pos)
{
	Vertex v[6];

	switch (_faceType)
	{
	case 0: //Top

		v[0].m_position = glm::vec3(0.5f, 0.5f, -0.5f) + pos;
		v[1].m_position = glm::vec3(-0.5f, 0.5f, 0.5f) + pos;
		v[2].m_position = glm::vec3(0.5f, 0.5f, 0.5f) + pos;

		v[3].m_position = glm::vec3(0.5f, 0.5f, -0.5f) + pos;
		v[4].m_position = glm::vec3(-0.5f, 0.5f, -0.5f) + pos;
		v[5].m_position = glm::vec3(-0.5f, 0.5f, 0.5f) + pos;

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
