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
			AddBlock(xOffset, yOffset);
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
	if (index < ARRAYSIZE) {
	
		//Instantiate the block position
		blocksPosition[index] = (glm::ivec3((index % DIM_BASE), (index / DIM_BASE) % DIM_HEIGHT, (index / (DIM_BASE * DIM_HEIGHT))));
		
		//Getting the value of simplexNoise with the position of blocks
		ind = simplex.fractal(7, (float)blocksPosition[index].x + pos.x, (float)blocksPosition[index].z + pos.z);
		ind *= 10;
		
		//Setting up Y position for the blocks to have a nice and smooth terrain.
		blocksPosition[index].y += ind  + 10;
		ind = index % 16 == 0 ? 0 : ind;
		
		//Fill all the terrain with gras blocks
		blocks[index] = Block(ID::Grass, true, true);
		blocks[index].SetCollider(BoxCollider(blocksPosition[index] + (glm::uvec3)pos));

		index++;
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
/*
void Chunk::CheckDirty()
{
	//std::cout << "Ready to check for dirty blocks" << std::endl;

	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		if (!blocks[i].IsDirty()) {
			continue;
		}
		else if (blocks[i].GetID() == ID::Air)
		{
			blocks[i].SetCollidable(false);
			blocks[i].SetOpaque(false);
			blocks[i].SetFaceToRender(Face::SKIP);

			//std::cout << "Block[" << i << "] ID: AIR Renders " << blocks[i].GetFace() << " Face" << std::endl;

			blocks[i].SetDirty(false);
			continue;
		}
		else
		{
			blocks[i].SetOpaque(true);
			blocks[i].SetCollidable(true);

			blocks[i].SetFaceToRender(Face::NOTHING);

			Block* neightbor = nullptr;

			neightbor = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x + 1, blocksPosition[i].y, blocksPosition[i].z));
			if (neightbor != nullptr)
			{
				if (neightbor->GetID() == ID::Air)
				{

					blocks[i].GetFace() &= ~Face::NOTHING;
					blocks[i].GetFace() |= Face::RIGHT;
				}
				else
				{
					blocks[i].GetFace() |= Face::RIGHT;
				}
			}
			else
			{
				blocks[i].GetFace() &= ~Face::NOTHING;
				blocks[i].GetFace() |= Face::RIGHT;
			}

			neightbor = nullptr;
			neightbor = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x - 1, blocksPosition[i].y, blocksPosition[i].z));
			if (neightbor != nullptr)
			{

				if (neightbor->GetID() == ID::Air)
				{

					blocks[i].GetFace() &= ~Face::NOTHING;
					blocks[i].GetFace() |= Face::LEFT;
				}
				else
				{
					blocks[i].GetFace() |=  Face::LEFT;
				}
			}
			else
			{
				blocks[i].GetFace() &= ~Face::NOTHING;
				blocks[i].GetFace() |= Face::LEFT;
			}

			neightbor = nullptr;
			neightbor = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x, blocksPosition[i].y + 1, blocksPosition[i].z));
			if (neightbor != nullptr)
			{

				if (neightbor->GetID() == ID::Air)
				{

					blocks[i].GetFace() &= ~Face::NOTHING;
					blocks[i].GetFace() |= Face::TOP;

				}
				else
				{
					blocks[i].GetFace() &= ~Face::TOP;
				}
			}
			else
			{
				blocks[i].GetFace() &= ~Face::NOTHING;
				blocks[i].GetFace() |= Face::TOP;
			}

			neightbor = nullptr;
			neightbor = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x, blocksPosition[i].y - 1, blocksPosition[i].z));
			if (neightbor != nullptr)
			{

				if (neightbor->GetID() == ID::Air)
				{

					blocks[i].GetFace() &= ~Face::NOTHING;
					blocks[i].GetFace() |= Face::BOTTOM;

				}
				else
				{
					blocks[i].GetFace() |= Face::BOTTOM;
				}
			}
			else
			{
				blocks[i].GetFace() &= ~Face::NOTHING;
				blocks[i].GetFace() |= Face::BOTTOM;
			}

			neightbor = nullptr;
			neightbor = GetBlockAtPosition(glm::vec3(blocksPosition[i].x, blocksPosition[i].y, blocksPosition[i].z + 1));
			if (neightbor != nullptr)
			{

				if (neightbor->GetID() == ID::Air)
				{

					blocks[i].GetFace() &= ~Face::NOTHING;
					blocks[i].GetFace() |= Face::FRONT;

				}
				else
				{
					blocks[i].GetFace() |= Face::FRONT;
				}
			}
			else
			{
				blocks[i].GetFace() &= ~Face::NOTHING;
				blocks[i].GetFace() |= Face::FRONT;
			}

			neightbor = nullptr;
			neightbor = GetBlockAtPosition(glm::vec3(blocksPosition[i].x, blocksPosition[i].y, blocksPosition[i].z - 1));
			if (neightbor != nullptr)
			{

				if (neightbor->GetID() == ID::Air)
				{

					blocks[i].GetFace() &= ~Face::NOTHING;
					blocks[i].GetFace() |= Face::BACK;
				}
				else
				{
					blocks[i].GetFace() |= Face::BACK;

				}
			}
			else
			{
				blocks[i].GetFace() &= ~Face::NOTHING;
				blocks[i].GetFace() |= Face::BACK;
			}
		}

		//std::cout << "Block[" << i << "] ID: GRASS Renders " << blocks[i].GetFace() << " Faces" << std::endl;
		blocks[i].SetDirty(false);
	}
}*/

void ChunkNS::Chunk::CheckDirty() 
{
	for (int i = 0; i < ARRAYSIZE; i++) {
		
		Block* neightbors[6] = { 
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y + 1,  blocksPosition[i].z	 ) + pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y - 1,  blocksPosition[i].z	 ) + pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x + 1,  blocksPosition[i].y,	  blocksPosition[i].z	 ) + pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x - 1,  blocksPosition[i].y,	  blocksPosition[i].z	 ) + pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z + 1) + pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z - 1) + pos)};


		for (int j = 0; j < (sizeof(neightbors) / sizeof(Block*)); j++) 
		{

			if (neightbors[j] == nullptr) {
				blocks[i].SetCollidable(true);
				blocks[i].SetOpaque(true);
				blocks[i].SetFaceToRender(Face::ALL);
				blocks[i].SetDirty(true);
			}
			else {
				blocks[i].SetFaceToRender(Face::SKIP);
			}
			//blocks[i].GetFace() |= (Face)j;
	
		}
			

		/*
		if((neightborUp    != nullptr && neightborUp->IsOpaque()    &&
			neightborDown  != nullptr && neightborDown->IsOpaque() &&
			neightborLeft  != nullptr && neightborLeft->IsOpaque() &&
			neightborRight != nullptr && neightborRight->IsOpaque() &&
			neightborFront != nullptr && neightborFront->IsOpaque() &&
			neightborBack  != nullptr && neightborBack->IsOpaque())
			|| blocks[i].GetID() == ID::Air)
			{

			blocks[i].SetCollidable(false);
			blocks[i].SetOpaque(false);
			blocks[i].SetFaceToRender(Face::SKIP);
			blocks[i].SetDirty(false);
		
		}
		else {
		
			blocks[i].SetCollidable(true);
			blocks[i].SetOpaque(true);
			blocks[i].SetFaceToRender(Face::ALL);
			blocks[i].SetDirty(true);
		}*/
		
	}
}

