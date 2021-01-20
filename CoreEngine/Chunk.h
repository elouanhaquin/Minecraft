#pragma once

#include "CoreEngineAPI.h"
#include <Block.h>
#include <glm\glm.hpp>
#include <Mesh.h>
#include <ChunkMesh.h>
#include <SimplexNoise.h>

using namespace BlockNS;
using namespace RenderEngineNS;


#define CHUNK_SIZE  16

#define CHUNK_ELEMENTS_COUNT (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)


namespace ChunkNS
{
	class COREENGINE_API Chunk
	{
	private:

		Block		blocks[CHUNK_ELEMENTS_COUNT];
		glm::uvec3	blocksPosition[CHUNK_ELEMENTS_COUNT];

		int index;
		int m_seed;
		float ind;
		SimplexNoise simplex;
		glm::ivec3	pos;
		ChunkMesh	Mesh;

	public:

		Chunk(glm::vec3 pos, int seed);

		~Chunk();

		inline Block*      GetBlocks()				{ return blocks != nullptr ? blocks : nullptr; }
		inline glm::uvec3* GetPositionArray()		{ return blocksPosition;					   }
		inline glm::uvec3  GetPosition()			{ return pos;								   }
		
		uint16_t			   From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z);
		std::array<uint8_t, 3> From1Dto3D(uint16_t p_index);
		Block*				   GetBlockAtPosition(glm::ivec3 _pos);

		void GenerateBlocks(int xOffset, int yOffset);
		void RenderFace();
		void AddFace(Face& _faceToDraw, glm::vec3 _pos);
		void Draw();
		void CheckDirty();

	};
}
