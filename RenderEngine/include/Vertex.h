#pragma once

#include "stdafx.h"

namespace RenderEngineNS
{
	struct Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec2 m_textureCoord;
	};
}