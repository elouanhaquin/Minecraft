#pragma once

#include "CoreEngineAPI.h"
#include <Block.h>
#include <Tree.h>
#include <glm\glm.hpp>
#include <Mesh.h>
#include <ChunkMesh.h>
#include <DecorationMesh.h>
#include <WaterMesh.h>
#include <SimplexNoise.h>


using namespace BlockNS;
using namespace RenderEngineNS;


#define CHUNK_SIZE  16

#define DECO_BLOCKS_MAX (CHUNK_SIZE * CHUNK_SIZE)
#define CHUNK_ELEMENTS_COUNT (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)


namespace ChunkNS
{
	class COREENGINE_API Chunk
	{
	private:
		struct NeighboursChunk
		{
			Chunk* left = nullptr;
			Chunk* right = nullptr;
			Chunk* bot = nullptr;
			Chunk* top = nullptr;
			Chunk* back = nullptr;
			Chunk* front = nullptr;
		};

		Block		blocks[CHUNK_ELEMENTS_COUNT];
		glm::ivec3	blocksPosition[CHUNK_ELEMENTS_COUNT];

		Block		waterBlocks[DECO_BLOCKS_MAX];
		glm::ivec3	waterBlocksPosition[DECO_BLOCKS_MAX];

		Tree* Trees[DECO_BLOCKS_MAX];

		Face chunkFace;
		int index;
		int m_seed;
		int m_treeCount;
		int m_waterCount;
		float ind;

		SimplexNoise simplex;
		glm::ivec3	pos;
		ChunkMesh	Mesh;
		DecorationMesh decoMesh;
		WaterMesh waterMesh;

		NeighboursChunk m_neighboursChunk;

	public:

		Chunk(glm::ivec3 pos, int seed);

		~Chunk();

		inline Block*      GetBlocks()				{ return blocks != nullptr ? blocks : nullptr; }
		inline glm::ivec3* GetPositionArray()		{ return blocksPosition;					   }
		inline glm::ivec3  GetPosition()			{ return pos;								   }
		inline Face		   GetFace()				{ return chunkFace;                            }
		inline ChunkMesh   GetMesh()				{ return Mesh;								   }
		
		uint16_t			   From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z);
		std::array<uint8_t, 3> From1Dto3D(uint16_t p_index);
		Block*				   GetBlockAtPosition(glm::ivec3 _pos);


		
		void shiftChunk(glm::ivec3 p_pos);
		void renderTrees();
		void renderWater();

		void GenerateBlocks(int xOffset, int yOffset);
		void fillChunk();
		void RenderFace();
		void updateChunk();
		void AddFace(Face& _faceToDraw, glm::vec3 _pos, ID _id );
		void Draw();
		void DrawDecoration();
		void DrawWater();
		void CheckDirty();
		void SetChunksNeighbour( Chunk* p_left, Chunk* p_right, Chunk*  p_top, Chunk* p_bot, Chunk*  p_front, Chunk* p_back);


	};
}
