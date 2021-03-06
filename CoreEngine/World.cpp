#include "stdafx.h"
#include <World.h>
#include <assert.h>
#include <map>

using namespace WorldNS;

World::World(/*const glm::vec3& _playerpos,*/ int width, int height) : worldHeight(height), worldWidth(width)
{
	assert(width > 0 && height > 0);

	worldDimension = worldWidth * worldWidth * worldHeight;


	for (int i = 0; i < worldDimension; ++i)
	{
		std::array<int16_t, 3> _pos = From1Dto3D(i);
		/*chunks.emplace_back(
			new Chunk(	glm::ivec3(	((i % worldWidth) * CHUNK_SIZE),(((i / worldWidth) % worldHeight)) * CHUNK_SIZE,((i / (worldWidth * worldHeight)) * CHUNK_SIZE)), 0));*/

		chunks.emplace_back(
			new Chunk(glm::ivec3( _pos.at(0), 0, _pos.at(2)), 0));
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

void WorldNS::World::addChunkTo(const glm::vec3 & p_pos)
{
	bool noChunkFound = false;

	for (int i = 0; i < this->GetChunks().size(); i++) 
		if (chunks[i]->GetPosition().x == p_pos.x
			&& chunks[i]->GetPosition().z == p_pos.z)
			noChunkFound = true;
	
	if (!noChunkFound) {
		Chunk* curr = new Chunk(glm::vec3(p_pos.x, 0, p_pos.z), 0);
		curr->GenerateBlocks(p_pos.x, p_pos.z);
		curr->RenderFace();
		chunks.emplace_back(curr);
	}
}

void WorldNS::World::generateChunkAroundPlayer(const glm::vec3 & p_pos)
{

	int x = p_pos.x / CHUNK_SIZE;
	int z = p_pos.z / CHUNK_SIZE;
	x *= CHUNK_SIZE;
	z *= CHUNK_SIZE;

	for (uint8_t i = 0; i < worldWidth; i++) {
		std::array<int16_t, 3> posChunk = From1Dto3D(i);

		//addChunkTo(glm::vec3(posChunk.at(0) + x, 0, posChunk.at(2) + z));
	}

}

void WorldNS::World::removeChunkAwayFromPlayer(const glm::vec3 & p_pos, const glm::vec3& p_dir)
{
	int x = (p_pos.x / CHUNK_SIZE);
	int z = (p_pos.z / CHUNK_SIZE);
	x *= CHUNK_SIZE;
	z *= CHUNK_SIZE;

	//glm::vec3 dir = glm::normalize(p_dir);
	checkNeighboursChunk();

	for (int i = 0; i < chunks.size(); i++)
	{
		int chunkX = chunks[i]->GetPosition().x;
		int chunkZ = chunks[i]->GetPosition().z;

		int distance = std::sqrt((std::pow((x - chunkX), 2) + std::pow((z - chunkZ), 2))) / CHUNK_SIZE;
		//int distanceX = std::sqrt((std::pow((x - chunkX), 2)));
		//int distanceZ = std::sqrt((std::pow((z - chunkZ), 2)));
		
		glm::vec3 distanceVec = glm::vec3(-(chunkX - x) + CHUNK_SIZE, 0, -(chunkZ - z) + CHUNK_SIZE);

		if (distance+4 > worldWidth / 2) {

			distanceVec = glm::ivec3(-(chunkX - x) , 0, -(chunkZ - z)) ;
			distanceVec = glm::ivec3(distanceVec.x / CHUNK_SIZE * CHUNK_SIZE, 0, distanceVec.z / CHUNK_SIZE * CHUNK_SIZE);
			glm::ivec3 newPos = glm::ivec3(chunks[i]->GetPosition() + (glm::ivec3)((distanceVec*1.75f)) / CHUNK_SIZE * CHUNK_SIZE);

			bool noChunkFound = false;

			for (int i = 0; i < this->GetChunks().size(); i++)
				if (chunks[i]->GetPosition().x == newPos.x
					&& chunks[i]->GetPosition().z == newPos.z)
					noChunkFound = true;

			if (!noChunkFound) 
				chunks[i]->shiftChunk(newPos);
		}
	}

	
			
}



void WorldNS::World::checkNeighboursChunk()
{
	for (int i = 0; i < chunks.size(); ++i)
	{

		glm::vec3 leftPos =  glm::vec3(chunks[i]->GetPosition().x + CHUNK_SIZE, chunks[i]->GetPosition().y, chunks[i]->GetPosition().z);
		glm::vec3 rightPos = glm::vec3(chunks[i]->GetPosition().x - CHUNK_SIZE, chunks[i]->GetPosition().y, chunks[i]->GetPosition().z);
		glm::vec3 botPos =   glm::vec3(chunks[i]->GetPosition().x , chunks[i]->GetPosition().y + CHUNK_SIZE, chunks[i]->GetPosition().z);
		glm::vec3 topPos =   glm::vec3(chunks[i]->GetPosition().x , chunks[i]->GetPosition().y - CHUNK_SIZE, chunks[i]->GetPosition().z);
		glm::vec3 backPos =  glm::vec3(chunks[i]->GetPosition().x , chunks[i]->GetPosition().y, chunks[i]->GetPosition().z + CHUNK_SIZE);
		glm::vec3 frontPos = glm::vec3(chunks[i]->GetPosition().x , chunks[i]->GetPosition().y, chunks[i]->GetPosition().z - CHUNK_SIZE);

		Chunk* left  = getChunkAtPos(leftPos) ;
		Chunk* right = getChunkAtPos(rightPos);
		Chunk* bot   = getChunkAtPos(botPos);
		Chunk* top   = getChunkAtPos(topPos);
		Chunk* back  = getChunkAtPos(backPos);
		Chunk* front = getChunkAtPos(frontPos);
		

		//chunks[i]->SetChunksNeighbour(left, right, bot, top, back, front);
		chunks[i]->SetChunksNeighbour(chunks[0], chunks[0], chunks[0], chunks[0], chunks[0], chunks[0]);
	}
}

void World::Render(const glm::vec3 p_playerPos, glm::vec3& p_view)
{
	m_skyBox.removeGPUData();


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
		glm::vec3 distance = (glm::vec3)chunks[i]->GetPosition() - p_playerPos;
		if (glm::dot(distance, glm::normalize(p_view)) + 100 > 0) chunks[i]->RenderFace();
		
	}
	for (int i = 0; i < 6; i++)
		m_skyBox.AddFace(i, glm::ivec3(p_playerPos.x -250, p_playerPos.y - 250, p_playerPos.z -250) , i);


	m_postProcess.createDepthTexture();
	m_postProcess.attachDepthTexture();


	m_skyBox.AddGPUData();
}

void World::Draw( glm::vec3& p_view, glm::vec3& p_playerPos)
{

	std::map<int, bool> renderIndices;

	m_skyBox.Draw(*ResourceManager::Instance().GetShader("SkyBox"), TimeNS::Time::dayTime);

	for (int i = 0; i < chunks.size(); ++i)
	{
		glm::vec3 distance = (glm::vec3)chunks[i]->GetPosition() - p_playerPos;
		if (glm::dot(distance, glm::normalize(p_view)) + 100  > 0) {
			renderIndices.emplace(i, true);
			chunks[i]->Draw(TimeNS::Time::dayTime);
		}
		else {
			renderIndices.emplace(i, false);
		}
			
	}
	for (int i = 0; i < chunks.size(); ++i)
	{
		if(renderIndices[i]) chunks[i]->DrawWater(TimeNS::Time::time);
	}
	for (int i = 0; i < chunks.size(); ++i)
	{
		if (renderIndices[i]) chunks[i]->DrawDecoration(TimeNS::Time::dayTime, TimeNS::Time::time);
	}

	
	m_postProcess.draw(*ResourceManager::Instance().GetShader("simpleDepthShader") , TimeNS::Time::time);

}

Chunk * WorldNS::World::getChunkAtPos(const glm::vec3 & p_pos)
{

	for (int i = 0; i < chunks.size(); ++i)
	{
		glm::ivec3 maxPos = glm::ivec3(chunks[i]->GetPosition().x + CHUNK_SIZE/2, 0, chunks[i]->GetPosition().z + CHUNK_SIZE/2);
		if ((p_pos.x < maxPos.x && p_pos.x > chunks[i]->GetPosition().x - CHUNK_SIZE/2)
		 && (p_pos.z < maxPos.z && p_pos.z > chunks[i]->GetPosition().z - CHUNK_SIZE/2))
			return chunks[i];
	}
	return nullptr;
}

uint16_t WorldNS::World::From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z)
{
	return ((p_x * worldWidth * worldHeight)  / CHUNK_SIZE) + ((p_z / CHUNK_SIZE) ); //Todo prendre en compte le p_y 
}

std::array<int16_t, 3> WorldNS::World::From1Dto3D(uint16_t p_index)
{
	std::array<int16_t, 3> result;

	result[2] = (p_index % worldWidth) * CHUNK_SIZE;					//Z				
	//p_index -= (std::get<2>(result) * (worldWidth * CHUNK_SIZE));
	result[1] = ((p_index / worldWidth) % worldHeight) * CHUNK_SIZE;	//Y		
	result[0] = p_index / (worldWidth *  worldHeight ) *  CHUNK_SIZE;  //X

	return result;
}

std::vector<Chunk*> WorldNS::World::GetChunks()
{
	return chunks;
}
