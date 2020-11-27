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
		chunks.emplace_back(
			new Chunk(	glm::ivec3(	((i % worldWidth) * DIM_BASE),
								(((i / worldWidth) % worldHeight)) * DIM_HEIGHT,
								((i / (worldWidth * worldHeight)) * DIM_BASE)),
			0));
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
	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

std::vector<Chunk*> WorldNS::World::GetChunks()
{
	return chunks;
}
