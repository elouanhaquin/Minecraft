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

Chunk::Chunk(glm::ivec3 _pos, int seed) : pos(_pos), index(0), Mesh(ChunkMesh()), simplex(SimplexNoise(0.020f,8.0f,1.0f,150.0f))
{
	m_seed = seed;
}


void Chunk::GenerateBlocks(int xOffset, int yOffset)
{
	fillChunk();
	CheckDirty();
	//addTree();
}

void ChunkNS::Chunk::fillChunk()
{
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
		
		if (ind > 0.75) {
			addTree(j, glm::ivec3(_pos.at(0) + pos.x, blocksInd + 1, _pos.at(1) + pos.z));
			j += 10;
		}

	}
	renderTrees();
}

void ChunkNS::Chunk::shiftChunk(glm::ivec3 p_pos)
{

	pos = p_pos;
	fillChunk();
	updateChunk();
	renderTrees();
}

void ChunkNS::Chunk::addTree(unsigned int p_index , glm::ivec3 p_pos)
{
	if (p_index + 10 > DECO_BLOCKS_MAX) return;

	decoBlocks[p_index]		= Block(ID::Wood, true, true);
	decoBlocks[p_index + 1] = Block(ID::Wood, true, true);
	decoBlocks[p_index + 2] = Block(ID::Wood, true, true);
	decoBlocks[p_index + 3] = Block(ID::Leaves, true, true);
	decoBlocks[p_index + 4] = Block(ID::Leaves, true, true);
	decoBlocks[p_index + 5] = Block(ID::Leaves, true, true);
	decoBlocks[p_index + 6] = Block(ID::Leaves, true, true);
	decoBlocks[p_index + 7] = Block(ID::Leaves, true, true);
	decoBlocks[p_index + 8] = Block(ID::Leaves, true, true);


	decoBlocksPosition[p_index]		= glm::ivec3(p_pos.x, p_pos.y, p_pos.z);
	decoBlocksPosition[p_index + 1] = glm::ivec3(p_pos.x, p_pos.y + 1, p_pos.z);
	decoBlocksPosition[p_index + 2] = glm::ivec3(p_pos.x, p_pos.y + 2, p_pos.z);
	decoBlocksPosition[p_index + 3] = glm::ivec3(p_pos.x, p_pos.y + 3, p_pos.z);
	decoBlocksPosition[p_index + 4] = glm::ivec3(p_pos.x + 1, p_pos.y + 3, p_pos.z);
	decoBlocksPosition[p_index + 5] = glm::ivec3(p_pos.x - 1, p_pos.y + 3, p_pos.z);
	decoBlocksPosition[p_index + 6] = glm::ivec3(p_pos.x, p_pos.y + 4, p_pos.z);
	decoBlocksPosition[p_index + 7] = glm::ivec3(p_pos.x, p_pos.y + 3, p_pos.z - 1);
	decoBlocksPosition[p_index + 8] = glm::ivec3(p_pos.x, p_pos.y + 3, p_pos.z + 1);

}

void ChunkNS::Chunk::renderTrees()
{
	//Only render top and bottom for leaves
	for (int i = 0; i < DECO_BLOCKS_MAX; i++){
		if (decoBlocks[i].GetID() != ID::Wood) {
			decoMesh.AddFace(0, decoBlocksPosition[i], (uint16_t)decoBlocks[i].GetID());
			decoMesh.AddFace(1, decoBlocksPosition[i], (uint16_t)decoBlocks[i].GetID());
		}

		decoMesh.AddFace(2, decoBlocksPosition[i], (uint16_t)decoBlocks[i].GetID());
		decoMesh.AddFace(3, decoBlocksPosition[i], (uint16_t)decoBlocks[i].GetID());
		decoMesh.AddFace(4, decoBlocksPosition[i], (uint16_t)decoBlocks[i].GetID());
		decoMesh.AddFace(5, decoBlocksPosition[i], (uint16_t)decoBlocks[i].GetID());
	}
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

void Chunk::Draw()
{
	Mesh.Draw(*ResourceManager::Instance().GetShader("Nano"));
}

void ChunkNS::Chunk::DrawDecoration()
{
	decoMesh.Draw(*ResourceManager::Instance().GetShader("Nano"));
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
	renderTrees();

	Mesh.AddGPUData();
	decoMesh.AddGPUData();
}

void ChunkNS::Chunk::updateChunk()
{
	decoMesh.removeGPUData();
	Mesh.removeGPUData();
	CheckDirty();
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
						blocks[i].SetFaceToRender(Face::ALL);

					case 1:
						blocks[i].GetFace() |= Face::TOP;
						blocks[i].GetFace() |= Face::BOTTOM;
						break;
					case 2:
						blocks[i].GetFace() |= Face::LEFT;
						blocks[i].GetFace() |= Face::RIGHT;
					case 3:
						blocks[i].GetFace() |= Face::LEFT;
						blocks[i].GetFace() |= Face::RIGHT;
					case 4:
						blocks[i].GetFace() |= Face::BACK;
						blocks[i].GetFace() |= Face::FRONT;
					case 5:
						blocks[i].GetFace() |= Face::FRONT;
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

