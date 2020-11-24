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
	//std::cout << "I'm Rendering" << std::endl;
}
/*
void Chunk::AddBlock(int xOffset, int yOffset)
{
	 blocksPosition[index] = (glm::ivec3((index % DIM_BASE),  (index / DIM_BASE) % DIM_HEIGHT + ind, (index / (DIM_BASE * DIM_HEIGHT)))+ (glm::ivec3)pos);
		if (index < ARRAYSIZE /*&& m_isRunning)
		{
			//switch (((index & 1) == 0))
			//{
			//case true:
			blocks[index] = Block(ID::Grass, true, true);
			blocks[index].SetCollider(BoxCollider(blocksPosition[index]+(glm::uvec3)pos));
			//break;

		//case false:
			//blocks[index] = Block(ID::Air, false, false);
			//break;
		//}
			
		
			index++;
			ind = simplex.fractal(7, (float)(index % DIM_BASE) + (xOffset* DIM_BASE), (float)(index / (DIM_BASE * DIM_HEIGHT) + ( yOffset* DIM_BASE))) + 1;
			ind *= 10;

			if (index % 16 == 0) 
			{
				ind = 0;
			}

			//AddFace(blocks[index].GetFace());
		}
}*/

void Chunk::AddBlock( int xOffset, int yOffset)
{
	if (index < ARRAYSIZE) {
		blocksPosition[index] = (glm::ivec3((index % DIM_BASE), (index / DIM_BASE) % DIM_HEIGHT + ind, (index / (DIM_BASE * DIM_HEIGHT))));

		blocks[index] = Block(ID::Grass, true, true);
		blocks[index].SetCollider(BoxCollider(blocksPosition[index] + (glm::uvec3)pos));
	
		index++;
		
		ind = simplex.fractal(7, (float)(index % DIM_BASE) + (yOffset * DIM_BASE), (float)(index / (DIM_BASE * DIM_HEIGHT) + (xOffset * DIM_BASE))) + 1;
		ind *= 10;
		ind = index % 16 == 0 ? 0 : ind; 

		//AddFace(blocks[index].GetFace(), pos);
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
		
		Block* neightborUp    = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y + 1, blocksPosition[i].z));
		Block* neightborDown  = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y - 1, blocksPosition[i].z));
		Block* neightborLeft  = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x - 1,  blocksPosition[i].y,	  blocksPosition[i].z));
		Block* neightborRight = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x + 1,  blocksPosition[i].y,	  blocksPosition[i].z));
		Block* neightborFront = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z + 1));
		Block* neightborBack  = GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z - 1));

		if((neightborUp    != nullptr && neightborUp->GetID() == ID::Grass    &&
			neightborDown  != nullptr && neightborDown->GetID() == ID::Grass  &&
			neightborLeft  != nullptr && neightborLeft->GetID() == ID::Grass  &&
			neightborRight != nullptr && neightborRight->GetID() == ID::Grass &&
			neightborFront != nullptr && neightborFront->GetID() == ID::Grass &&
			neightborBack  != nullptr && neightborBack->GetID() == ID::Grass)
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
		}
		
	}
}

