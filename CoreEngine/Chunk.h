#pragma once

#include "CoreEngineAPI.h"
#include <Block.h>
#include <glm\glm.hpp>
#include <Mesh.h>
#include <ChunkMesh.h>
#include <SimplexNoise.h>

using namespace BlockNS;
using namespace RenderEngineNS;

#define DIM_HEIGHT	6
#define DIM_BASE	16

#define ARRAYSIZE (DIM_BASE * DIM_BASE * DIM_HEIGHT)


namespace ChunkNS
{
	class COREENGINE_API Chunk
	{
	public:

		Chunk(glm::vec3 pos, int seed);

		~Chunk();

		inline Block* GetBlocks()				{ return blocks != nullptr ? blocks : nullptr; }

		inline glm::uvec3* GetPositionArray()	{ return blocksPosition; }

		inline glm::uvec3 GetPosition()			{ return pos; }

		void GenerateBlocks( int xOffset, int yOffset);

		void AddBlock(int xOffset, int yOffset);

		Block* GetBlockAtPosition(glm::ivec3 _pos);

		void RenderFace();

		void AddFace(Face& _faceToDraw, glm::vec3 _pos);

		void Draw();

		void CheckDirty();

		void CheckDirtyBlock();

	private:

		Block		blocks[ARRAYSIZE];
		glm::uvec3	blocksPosition[ARRAYSIZE];

		int index;
		int m_seed;
		float ind;
		SimplexNoise simplex;


		glm::ivec3	pos;
		ChunkMesh	Mesh;
	};
}
