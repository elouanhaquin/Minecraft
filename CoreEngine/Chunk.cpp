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
	
	/*for (int i = 0; i < ARRAYSIZE; ++i)
	{
		//AddBlock(xOffset, yOffset);
		pos.y = 0;
		ind = simplex.fractal(7, i % DIM_BASE + pos.x, (i / DIM_BASE) % DIM_BASE + pos.z);
		ind *= 10;
		ind = DIM_HEIGHT / 2 + ind;

		glm::ivec3  posBlock = (glm::ivec3(i % DIM_BASE, (i / DIM_BASE) / DIM_BASE -ind, (i / DIM_BASE) % DIM_BASE));
		posBlock.y *= -1;
		blocksPosition[i] = posBlock + pos;
		blocks[i] = Block(ID::Grass, true, true);
		blocks[i].SetCollider(BoxCollider(blocksPosition[i] + (glm::uvec3)pos));
	}*/

	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		std::array<uint8_t, 3> _pos = From1Dto3D(i);
		blocksPosition[i] = glm::ivec3(_pos.at(0), _pos.at(1), _pos.at(2));
		blocks[i].SetCollider(BoxCollider(blocksPosition[i] + (glm::uvec3)pos));
	}
	
	CheckDirty();
}

std::array<uint8_t, 3> ChunkNS::Chunk::From1Dto3D(uint16_t p_index)
{
	std::array<uint8_t, 3> result;
	result[2] = p_index / (ARRAYSIZE * ARRAYSIZE);
	p_index -= (std::get<2>(result) * (ARRAYSIZE * ARRAYSIZE));
	result[1] = p_index / ARRAYSIZE;
	result[0] = p_index % ARRAYSIZE;
	return result;
}

uint16_t ChunkNS::Chunk::From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z)
{
	return p_x + p_y * ARRAYSIZE + p_z * ARRAYSIZE * ARRAYSIZE;
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
		AddFace(blocks[i].GetFace(), this->blocksPosition[i]);
	}
	Mesh.AddGPUData();
}

Block* Chunk::GetBlockAtPosition(glm::ivec3 _pos)
{

	if ((_pos.x < DIM_BASE && _pos.y < DIM_HEIGHT && _pos.z < DIM_BASE) && (_pos.x >= 0 && _pos.y >= 0 && _pos.z >= 0)) {
	
		int posArray = (_pos.x + DIM_BASE * (_pos.y + DIM_HEIGHT * _pos.z));
		/*if (blocksPosition[posArray] == (glm::uvec3)_pos) {
			*///std::cout << "X : " << _pos.x << " Y: " << _pos.y << " Z: " << _pos.z << std::endl;
		/*}*/

		return &blocks[posArray];
	}

	return nullptr;
	//return &blocks[(_pos.x *DIM_BASE) + (_pos.y  * DIM_HEIGHT) +  (_pos.z + DIM_BASE)];

	

	//return &blocks[((_pos.x *DIM_BASE) + (_pos.y  * DIM_HEIGHT) + (_pos.z + DIM_BASE))] != nullptr ? &blocks[(_pos.x *DIM_BASE) + (_pos.y  * DIM_HEIGHT) + (_pos.z + DIM_BASE)] : nullptr;
}

void ChunkNS::Chunk::CheckDirty() 
{
	//std::cout << "X : " << pos.x << " Y: " << pos.y << " Z: " << pos.z << std::endl;

	for (int i = 0; i < ARRAYSIZE; i++) {
		
		Block* neightbors[6] = { 
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y + 1,  blocksPosition[i].z		) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y - 1,  blocksPosition[i].z		) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x + 1,  blocksPosition[i].y,	  blocksPosition[i].z		) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x - 1,  blocksPosition[i].y,	  blocksPosition[i].z		) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z + 1	) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z - 1 	) - pos)};
		

		for (int j = 0; j <= (sizeof(neightbors) / sizeof(Block*)); j++) 
		{
			if (neightbors[j] == nullptr ) {
				
				blocks[i].SetCollidable(true);
				blocks[i].SetOpaque(true);
				blocks[i].SetFaceToRender(Face::ALL);
				blocks[i].SetDirty(true);
				//i++;
				break;
			}
			else {
				blocks[i].SetOpaque(false);
				blocks[i].SetFaceToRender(Face::NOTHING);
			}
			//blocks[i].GetFace() |= (Face)j;
	
		}
			
	
	}
}

