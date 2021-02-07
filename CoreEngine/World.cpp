#include "stdafx.h"
#include <World.h>
#include <assert.h>

using namespace WorldNS;

World::World(/*const glm::vec3& _playerpos,*/ int width, int height) : worldHeight(height), worldWidth(width)
{
	assert(width > 0 && height > 0);

	worldDimension = worldWidth * worldWidth * worldHeight;

	for (int i = 0; i < worldDimension; ++i)
	{
		std::array<uint8_t, 3> _pos = From1Dto3D(i);
		/*chunks.emplace_back(
			new Chunk(	glm::ivec3(	((i % worldWidth) * CHUNK_SIZE),(((i / worldWidth) % worldHeight)) * CHUNK_SIZE,((i / (worldWidth * worldHeight)) * CHUNK_SIZE)), 0));*/
		chunks.emplace_back(
			new Chunk(glm::ivec3( _pos.at(0), _pos.at(1), _pos.at(2)), 0));
	}
}

World::~World()
{
	m_isRunning = false;
	for (auto& thread : m_chunkLoadThreads) {
		thread.join();
	}
}

void World::Populate()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	m_chunkLoadThreads.emplace_back([&]()
	{
		int xOffset = 0;
		int yOffset = 0;

		for (int i = 0; i < chunks.size(); ++i, ++xOffset)
		{
			if(i % (int)sqrt(chunks.size()) == 0 )
			{
				yOffset++;
				xOffset = 0;
			}
			chunks[i]->GenerateBlocks(xOffset, yOffset);
		}
	});
}


void WorldNS::World::checkNeighboursChunk()
{
	for (int i = 0; i < chunks.size(); ++i)
	{
		std::array<uint8_t, 3> posChunk = From1Dto3D(i);

		Chunk* left  = posChunk.at(0) > 0	?	chunks[From3Dto1D(posChunk.at(0) - CHUNK_SIZE, posChunk.at(1), posChunk.at(2))] : nullptr;
		Chunk* right = posChunk.at(0) < 144	?	chunks[From3Dto1D(posChunk.at(0) + CHUNK_SIZE, posChunk.at(1), posChunk.at(2))] : nullptr;//
		Chunk* bot   = posChunk.at(1) > 0	?	chunks[From3Dto1D(posChunk.at(0), posChunk.at(1) - CHUNK_SIZE, posChunk.at(2))] : nullptr;
		Chunk* top   = posChunk.at(1) < 144 ?	chunks[From3Dto1D(posChunk.at(0), posChunk.at(1) + CHUNK_SIZE, posChunk.at(2))] : nullptr;
		Chunk* back  = posChunk.at(2) > 0	?	chunks[From3Dto1D(posChunk.at(0), posChunk.at(1), posChunk.at(2) - CHUNK_SIZE)] : nullptr;
		Chunk* front = posChunk.at(2) < 144 ?	chunks[From3Dto1D(posChunk.at(0), posChunk.at(1), posChunk.at(2) + CHUNK_SIZE)] : nullptr;//

		chunks[i]->SetChunksNeighbour(left, right, bot, top, back, front);
	}
}

void World::Render()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	if (m_isRunning)
	{
		for (auto& thread : m_chunkLoadThreads) {
			thread.join();
		}
	}

	for (int i = 0; i < chunks.size(); ++i)
	{
		checkNeighboursChunk();
		chunks[i]->RenderFace();
	}
}

void World::Draw()
{
	for (int i = 0; i < chunks.size(); ++i)
	{
		chunks[i]->Draw();
	}
}

uint16_t WorldNS::World::From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z)
{
	return ((p_x * worldWidth * worldHeight)  / CHUNK_SIZE) + ((p_z / CHUNK_SIZE) ); //Todo prendre en compte le p_y 
}

std::array<uint8_t, 3> WorldNS::World::From1Dto3D(uint16_t p_index)
{
	std::array<uint8_t, 3> result;

	result[2] = (p_index % worldWidth) * CHUNK_SIZE;					//Z				
	//p_index -= (std::get<2>(result) * (worldWidth * worldWidth));
	result[1] = ((p_index / worldWidth) % worldHeight) * CHUNK_SIZE;	//Y		
	result[0] = ((p_index / (worldWidth * worldHeight)) * CHUNK_SIZE);  //X

	return result;
}

std::vector<Chunk*> WorldNS::World::GetChunks()
{
	return chunks;
}
