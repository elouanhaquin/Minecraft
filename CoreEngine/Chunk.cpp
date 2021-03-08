#include "stdafx.h"
#include <Chunk.h>

#include <ShaderCore.h>
#include <ResourceManager.h>


using namespace ChunkNS;

Chunk::Chunk(glm::ivec3 _pos, int seed) : pos(_pos), index(0), Mesh(ChunkMesh()), simplex(SimplexNoise(0.020f,8.0f,1.0f,150.0f))
{
	m_seed = seed;
	m_treeCount = 0;
	m_waterCount = 0;
}


void Chunk::GenerateBlocks(int xOffset, int yOffset)
{
	fillChunk();
	CheckDirty();
}

void ChunkNS::Chunk::fillChunk()
{
	m_treeCount = 0;
	m_waterCount = 0;
	m_grassCount = 0;

	
	for (int i = 0; i < CHUNK_ELEMENTS_COUNT; ++i)
	{
		std::array<uint8_t, 3> _pos = From1Dto3D(i);
		blocksPosition[i] = glm::ivec3(_pos.at(0), _pos.at(1), _pos.at(2)) + (glm::ivec3)pos;

		ind = simplex.fractal(7, blocksPosition[i].x, blocksPosition[i].z);

		ind *= 5;
		ind += 10;

		if (_pos.at(1) > ind) {
			blocks[i] = Block(ID::Air, false, false);
		}
		else {
			blocks[i].SetCollider(BoxCollider(blocksPosition[i] + (glm::ivec3)pos));
			blocks[i] =  blocksPosition[i].y < 2 ?  Block(ID::BedRock, true, true) : Block(ID::Stone, true, true);	
			blocks[i] =  blocksPosition[i].y > ind - 3 ? Block(ID::Grass, true, true) : Block(ID::Stone, true, true);
			if (ind <= 10) blocks[i] = Block(ID::Sand, true, true);
		}
	}

	float blocksInd = 0.0f;
	for (int j = 0; j < DECO_BLOCKS_MAX; j++)
	{
		std::array<uint8_t, 3> _pos = From1Dto3D(j);
		
		blocksInd = simplex.fractal(7, _pos.at(0) + pos.x, _pos.at(1) + pos.z) ;
		ind = simplex.noise(_pos.at(0), _pos.at(1));
		blocksInd *= 5;
		blocksInd += 10;	
		
		if (blocksInd < 9) {
			if (waterBlocks[m_waterCount].GetID() != ID::Water) {
				waterBlocks[m_waterCount] =  Block(ID::Water, true, true);
			}
			waterBlocksPosition[m_waterCount] = glm::ivec3(_pos.at(0) + pos.x, 9, _pos.at(1) + pos.z);
			m_waterCount++;
		
		}

		if (ind > 0.95 && blocksInd > 10) {
			glm::ivec3 newPos = glm::ivec3(_pos.at(0) + pos.x, blocksInd + 1, _pos.at(1) + pos.z);
			Trees[m_treeCount] = Trees[m_treeCount] == nullptr ? new Tree(newPos) : Trees[m_treeCount]->moveTo(newPos);
			m_treeCount++;
		}
		else if (ind < 0.95  && ind > 0.25 && blocksInd > 10) {
			glm::ivec3 newPos = glm::ivec3(_pos.at(0) + pos.x, blocksInd + 1, _pos.at(1) + pos.z);
			grassBlocks[m_grassCount] = new Block(ID::Weeds, true, true);
			grassBlocksPosition[m_grassCount] = newPos;
			m_grassCount++;
		}
	}

	renderWater();
	renderTrees();
	
	
}

void ChunkNS::Chunk::shiftChunk(glm::ivec3 p_pos)
{
	pos = p_pos;
	
	if (Trees != nullptr)
		for (int i = 0; Trees[i] != nullptr && i < m_treeCount; i++)
			 Trees[i] == nullptr;

	for (int i = 0; grassBlocks[i] != nullptr && i < m_grassCount; i++)
		delete grassBlocks[i];
	
	
	
	fillChunk();
	updateChunk();


	//renderWater();
	//renderTrees();


}

void ChunkNS::Chunk::renderTrees()
{
	//Only render top and bottom for leaves


	for (unsigned int i = 0; Trees[i] != nullptr && i < m_treeCount; i++){
		for (unsigned int j = 0; Trees[i]->getBlock(j) != nullptr && j < 9; j++) {
			if (Trees[i]->getBlock(j)->GetID() != ID::Wood) {
				decoMesh.AddFace(0, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				decoMesh.AddFace(1, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
			}
			if (j <= 2) {
				Mesh.AddFace(2, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				Mesh.AddFace(3, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				Mesh.AddFace(4, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				Mesh.AddFace(5, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
			}
			else {
				decoMesh.AddFace(2, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				decoMesh.AddFace(3, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				decoMesh.AddFace(4, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
				decoMesh.AddFace(5, Trees[i]->getPos(j), (uint16_t)Trees[i]->getBlock(j)->GetID());
			}
		
		}
	}
	 
	for (unsigned int i = 0; i < m_grassCount; i++) {
		decoMesh.AddFace(6, grassBlocksPosition[i], (uint16_t)grassBlocks[i]->GetID());
		decoMesh.AddFace(7, grassBlocksPosition[i], (uint16_t)grassBlocks[i]->GetID());
		decoMesh.AddFace(8, grassBlocksPosition[i], (uint16_t)grassBlocks[i]->GetID());
		decoMesh.AddFace(9, grassBlocksPosition[i], (uint16_t)grassBlocks[i]->GetID());
	}
}

void ChunkNS::Chunk::renderWater()
{

	for (unsigned int i = 0; i < m_waterCount; i++)
		if (waterBlocks[i].GetID() != ID::Air) 
			waterMesh.AddFace(0, waterBlocksPosition[i], (uint16_t)waterBlocks[i].GetID());

	
}

std::array<uint8_t, 3> ChunkNS::Chunk::From1Dto3D(uint16_t p_index)
{
	std::array<uint8_t, 3> result;
	result[2] = p_index / (CHUNK_SIZE * CHUNK_SIZE);
	p_index -= (std::get<2>(result) * (CHUNK_SIZE * CHUNK_SIZE));
	result[1] = p_index / CHUNK_SIZE;
	result[0] = p_index % CHUNK_SIZE;
	return result;
}

uint16_t ChunkNS::Chunk::From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z)
{
	return p_x + p_y * CHUNK_SIZE + p_z * CHUNK_SIZE * CHUNK_SIZE;
}

Chunk::~Chunk()
{
	/*m_isRunning = false;
	for (auto& thread : m_chunkLoadThreads) {
		thread.join();
	}*/
	
	//delete []blocks;
	//delete []blocksPosition;
}

void Chunk::Draw(float p_time)
{
	
	Mesh.Draw(*ResourceManager::Instance().GetShader("Nano"), p_time);
}

void ChunkNS::Chunk::DrawDecoration(float p_dayTime, float p_time)
{
	decoMesh.Draw(*ResourceManager::Instance().GetShader("LeavesEffect"), p_dayTime, p_time);
}

void ChunkNS::Chunk::DrawWater(float p_time)
{
	waterMesh.Draw(*ResourceManager::Instance().GetShader("WaterEffect"), p_time);
}


void Chunk::AddFace(Face& _faceToAdd, glm::vec3 _pos, ID _id)
{
	if ((_faceToAdd == Face::NOTHING) || (_faceToAdd == Face::SKIP))
		return;

	if ((_faceToAdd & Face::TOP		)	== Face::TOP	)	Mesh.AddFace(0, _pos, (uint16_t)_id);
	if ((_faceToAdd & Face::BOTTOM	)	== Face::BOTTOM	)	Mesh.AddFace(1, _pos, (uint16_t)_id);
	if ((_faceToAdd & Face::FRONT	)	== Face::FRONT	)	Mesh.AddFace(2, _pos, (uint16_t)_id);
	if ((_faceToAdd & Face::BACK	)	== Face::BACK	)	Mesh.AddFace(3, _pos, (uint16_t)_id);
	if ((_faceToAdd & Face::RIGHT	)	== Face::RIGHT	)	Mesh.AddFace(4, _pos, (uint16_t)_id);
	if ((_faceToAdd & Face::LEFT	)	== Face::LEFT	)	Mesh.AddFace(5, _pos, (uint16_t)_id);
}

void Chunk::RenderFace()
{
	for (int i = 0; i < CHUNK_ELEMENTS_COUNT; ++i)
	{
		if (( From1Dto3D(i).at(0) == 0              && m_neighboursChunk.left  != nullptr)
		|| (  From1Dto3D(i).at(2) == 0              && m_neighboursChunk.front != nullptr)
		|| (  From1Dto3D(i).at(0) == CHUNK_SIZE - 1 && m_neighboursChunk.right != nullptr)
		|| (  From1Dto3D(i).at(2) == CHUNK_SIZE - 1 && m_neighboursChunk.back  != nullptr))
		{
			
			if(((GetBlockAtPosition(glm::ivec3(blocksPosition[i].x, blocksPosition[i].y + 1, blocksPosition[i].z) - pos))!= nullptr
			&&  (GetBlockAtPosition(glm::ivec3(blocksPosition[i].x, blocksPosition[i].y + 1, blocksPosition[i].z) - pos))->GetID() == ID::Air))
				AddFace(blocks[i].GetFace(), this->blocksPosition[i], blocks[i].GetID());
		}
		else {
			if (blocks[i].GetID() != ID::Air && !(From1Dto3D(i).at(1) == 0))
				AddFace(blocks[i].GetFace(), this->blocksPosition[i], blocks[i].GetID());
		}

	  (From1Dto3D(i).at(0) == 0				 && m_neighboursChunk.left  == nullptr && blocks[i].GetID() != ID::Air) ? AddFace(blocks[i].GetFace(), this->blocksPosition[i], blocks[i].GetID()) : (void)0;
	  (From1Dto3D(i).at(2) == 0				 && m_neighboursChunk.front == nullptr && blocks[i].GetID() != ID::Air)	? AddFace(blocks[i].GetFace(), this->blocksPosition[i], blocks[i].GetID()) : (void)0;
	  (From1Dto3D(i).at(0) == CHUNK_SIZE - 1 && m_neighboursChunk.right == nullptr && blocks[i].GetID() != ID::Air) ? AddFace(blocks[i].GetFace(), this->blocksPosition[i], blocks[i].GetID()) : (void)0;
	  (From1Dto3D(i).at(2) == CHUNK_SIZE - 1 && m_neighboursChunk.back  == nullptr && blocks[i].GetID() != ID::Air) ? AddFace(blocks[i].GetFace(), this->blocksPosition[i], blocks[i].GetID()) : (void)0;
	}



	Mesh.AddGPUData();
	decoMesh.AddGPUData();
	waterMesh.AddGPUData();
}

void ChunkNS::Chunk::updateChunk()
{
	decoMesh.removeGPUData();
	Mesh.removeGPUData();
	waterMesh.removeGPUData();


	CheckDirty();

	renderWater();
	renderTrees();
	RenderFace();
	

}

Block* Chunk::GetBlockAtPosition(glm::ivec3 _pos)
{

	if ((_pos.x < CHUNK_SIZE && _pos.y < CHUNK_SIZE && _pos.z < CHUNK_SIZE) && (_pos.x >= 0 && _pos.y >= 0 && _pos.z >= 0)) {	
		int posArray = (_pos.x + CHUNK_SIZE * (_pos.y + CHUNK_SIZE * _pos.z));
		return &blocks[posArray];
	}
	return nullptr;

}

void ChunkNS::Chunk::CheckDirty() 
{
	for (int i = 0; i < CHUNK_ELEMENTS_COUNT; i++) {
		
		if (blocks[i].GetID() == ID::Air) {
			blocks[i].SetOpaque(false);
			blocks[i].SetFaceToRender(Face::NOTHING);
		}
		else {
			Block* neightbors[6] = {
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y + 1,  blocksPosition[i].z) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y - 1,  blocksPosition[i].z) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x + 1,  blocksPosition[i].y,	  blocksPosition[i].z) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x - 1,  blocksPosition[i].y,	  blocksPosition[i].z) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z + 1) - pos),
				GetBlockAtPosition(glm::ivec3(blocksPosition[i].x,		blocksPosition[i].y,	  blocksPosition[i].z - 1) - pos)};

			for (int j = 0; j < (sizeof(neightbors) / sizeof(Block*)); j++)
			{
				if (neightbors[j] == nullptr || neightbors[j]->GetID() == ID::Air) {

					blocks[i].SetCollidable(true);
					blocks[i].SetOpaque(true);

					switch (j) {
					case 0:
						blocks[i].GetFace() |= Face::TOP;
					case 1:
						blocks[i].GetFace() |= Face::BOTTOM;
					case 2:
						blocks[i].GetFace() |= Face::RIGHT;
					case 3:
						blocks[i].GetFace() |= Face::LEFT;
					case 4:
						blocks[i].GetFace() |= Face::FRONT;
					case 5:
						blocks[i].GetFace() |= Face::BACK;
					}
					blocks[i].SetDirty(true);

					break;
				}
				else {
					blocks[i].SetOpaque(false);
					blocks[i].SetFaceToRender(Face::NOTHING);						
				}
				
			}
		}		
	}
}

void ChunkNS::Chunk::SetChunksNeighbour(Chunk * p_left, Chunk * p_right, Chunk * p_top, Chunk * p_bot, Chunk * p_front, Chunk * p_back)
{
	m_neighboursChunk.left = p_left;
	m_neighboursChunk.right = p_right;
	m_neighboursChunk.top = p_top;
	m_neighboursChunk.bot = p_bot;
	m_neighboursChunk.front = p_front;
	m_neighboursChunk.back = p_back;

}

