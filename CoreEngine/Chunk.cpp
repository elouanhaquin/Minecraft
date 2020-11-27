#include "stdafx.h"
#include <Chunk.h>

#include <ShaderCore.h>
#include <ResourceManager.h>

/*
TODO:
	-Check if cube is dirty and update
	-Update Face Culling
	-Generate Mesh
	-Instancing
*/

using namespace ChunkNS;

Chunk::Chunk(glm::vec3 _pos, int seed) : pos(_pos), index(0), Mesh(ChunkMesh()), simplex(SimplexNoise(0.015f,8.0f,1.0f,1.0f))
{
	m_seed = seed;
}

void Chunk::GenerateBlocks(int xOffset, int yOffset)
{
	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		//AddBlock(xOffset, yOffset);

		ind = simplex.fractal(7, i % DIM_BASE + pos.x, (i / DIM_BASE) % DIM_BASE + pos.z);
		ind *= 10;
		ind = DIM_HEIGHT / 2 + ind;

		glm::ivec3  posBlock = (glm::ivec3(i % DIM_BASE, (i / DIM_BASE) / DIM_BASE - ind, (i / DIM_BASE) % DIM_BASE));
		blocksPosition[i] = posBlock;
		blocks[i] = Block(ID::Grass, true, true);
		blocks[i].SetCollider(BoxCollider(blocksPosition[i] + (glm::uvec3)pos));

	}

	CheckDirty();
}

Chunk::~Chunk()
{
	/*m_isRunning = false;
	for (auto& thread : m_chunkLoadThreads) {
		thread.join();
	}*/
}

void Chunk::Draw()
{
	Mesh.Draw(*ResourceManager::Instance().GetShader("Nano"));
}

void Chunk::AddBlock( int xOffset, int yOffset)
{
	/*if (index < DIM_BASE * DIM_BASE *10 ) {
			blocksPosition[index] = (glm::ivec3(index % DIM_BASE, (index / DIM_BASE) / DIM_BASE, (index / DIM_BASE) % DIM_BASE));

			if (index < DIM_BASE * DIM_BASE * BEDROCK) {
				blocks[index] = Block(ID::BedRock, true, true);
			}
			else {
				blocks[index] = Block(ID::Stone, true, true);
			}
			
			blocks[index].SetCollider(BoxCollider(blocksPosition[index] + (glm::uvec3)pos));
			index++;
	}
	else if(index < DIM_BASE * DIM_BASE * 30) {
		//Instantiate the block position
		//blocksPosition[index] = (glm::ivec3((index / DIM_BASE) , (index / (DIM_BASE * DIM_HEIGHT)),   (index % DIM_BASE) % DIM_HEIGHT ));
		blocksPosition[index] = (glm::ivec3(index % DIM_BASE, (index / DIM_BASE) / DIM_BASE, (index / DIM_BASE) % DIM_BASE));
		
		//Getting the value of simplexNoise with the position of blocks	
		ind = simplex.fractal(7, (float)blocksPosition[index].x + pos.x, (float)blocksPosition[index].z + pos.z);
		ind *= 10;
		blocksPosition[index].y += ind;
		
		//Setting up Y position for the blocks to have a nice and smooth terrain.
	/*	int count = index;
		int yOffset = 0;

		glm::ivec3 posBlock = glm::ivec3(index % DIM_BASE, (index / DIM_BASE) / DIM_BASE - count, (index / DIM_BASE) % DIM_BASE);
		//std::cout << blocksPosition[count].y << " vs " << blocksPosition[index].y << std::endl;
		while (yOffset <  ind && count < ARRAYSIZE) {
			count++;
			posBlock = (glm::ivec3(index % DIM_BASE, (index / DIM_BASE) / DIM_BASE + yOffset, (index / DIM_BASE) % DIM_BASE));
			blocksPosition[count] = posBlock;
			blocks[count] = Block(ID::Grass, true, true);
			blocks[count].SetCollider(BoxCollider(blocksPosition[count] + (glm::uvec3)pos));
			
			yOffset++;
		}
		index = count;

		//blocksPosition[index].y += ind ;
		ind = index % 16 == 0 ? 0 : ind;
		
		//Fill all the terrain with grass blocks
		if (index % DIM_HEIGHT == 0) {

			blocks[index] = Block(ID::Grass, true, true);
			blocks[index].SetCollider(BoxCollider(blocksPosition[index] + (glm::uvec3)pos));

		}
		else {
			//blocks[index] = Block(ID::Grass, false, false);
		}

		index++;
	}*/

	 
	}
}

void Chunk::AddFace(Face& _faceToAdd, glm::vec3 _pos)
{
	if ((_faceToAdd == Face::NOTHING) || (_faceToAdd == Face::SKIP))
		return;

	if ((_faceToAdd & Face::TOP		)	== Face::TOP	)	Mesh.AddFace(0, _pos);
	if ((_faceToAdd & Face::BOTTOM	)	== Face::BOTTOM	)	Mesh.AddFace(1, _pos);
	if ((_faceToAdd & Face::FRONT	)	== Face::FRONT	)	Mesh.AddFace(2, _pos);
	if ((_faceToAdd & Face::BACK	)	== Face::BACK	)	Mesh.AddFace(3, _pos);
	if ((_faceToAdd & Face::RIGHT	)	== Face::RIGHT	)	Mesh.AddFace(4, _pos);
	if ((_faceToAdd & Face::LEFT	)	== Face::LEFT	)	Mesh.AddFace(5, _pos);
}

void Chunk::RenderFace()
{
	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		AddFace(blocks[i].GetFace(), this->blocksPosition[i] + (glm::uvec3)pos);
	}
	Mesh.AddGPUData();
}

Block* Chunk::GetBlockAtPosition(glm::ivec3 _pos)
{
	if((_pos.x < DIM_BASE && _pos.y < DIM_HEIGHT && _pos.z < DIM_BASE) && (_pos.x >= 0 && _pos.y >= 0 && _pos.z >= 0))
		return &blocks[(_pos.x + DIM_BASE * (_pos.y + DIM_HEIGHT * _pos.z))];

	return nullptr;
}

void ChunkNS::Chunk::CheckDirty() 
{
	for (int i = 0; i < ARRAYSIZE; i++) {
		
		Block* neightbors[6] = { 
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y + 1,  blocksPosition[i].z	 ) ),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y - 1,  blocksPosition[i].z	 ) ),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x + 1,  blocksPosition[i].y,	  blocksPosition[i].z	 ) ),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x - 1,  blocksPosition[i].y,	  blocksPosition[i].z	 ) ),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z + 1) ),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z - 1) )};


		for (int j = 0; j < (sizeof(neightbors) / sizeof(Block*)); j++) 
		{

			//if (neightbors[j] == nullptr ) {
				blocks[i].SetCollidable(true);
				blocks[i].SetOpaque(true);
				blocks[i].SetFaceToRender(Face::ALL);
				blocks[i].SetDirty(true);
				
			//}
			//else {
			//	blocks[i].SetOpaque(false);
			//	blocks[i].SetFaceToRender(Face::NOTHING);
			//}
			//blocks[i].GetFace() |= (Face)j;
	
		}
			
		
	}
}

