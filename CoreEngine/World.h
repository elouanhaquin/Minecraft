#pragma once

#include "CoreEngineAPI.h"
#include "SkyBox.h"
#include "PostProcessing.h"
#include "include\ResourceManager.h"
#include <memory>
#include <Chunk.h>
#include <atomic>
#include <thread>

using namespace CoreEngineNS;
using namespace ChunkNS;

namespace WorldNS
{
	class COREENGINE_API World
	{

	public:
		World(/*const glm::vec3& _playerPos,*/ int width, int height);
		~World();

		void Populate();
		void addChunkTo(const glm::vec3& p_pos);
		void generateChunkAroundPlayer(const glm::vec3& p_pos);
		void removeChunkAwayFromPlayer(const glm::vec3& p_pos, const glm::vec3& p_dir);
		void destroyBlockAt(const glm::vec3& p_pos, const glm::vec3& p_dir);
		void checkNeighboursChunk();
		
		void Render(const glm::vec3 p_playerPos, glm::vec3& p_view);
		void Draw( glm::vec3& p_view, glm::vec3& p_playerPos);

		inline int getWidth() { return worldWidth; }
		Chunk* getChunkAtPos(const glm::vec3& p_pos);
		

		uint16_t			   From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z);
		std::array<int16_t, 3> From1Dto3D(uint16_t p_index);


	private:

		int worldDimension;
		int worldWidth;
		int worldHeight;

		SkyBox m_skyBox;
		PostProcessing m_postProcess;

		std::vector<Chunk*> chunks;

		std::atomic<bool>			m_isRunning{ true };
		std::vector<std::thread>	m_chunkLoadThreads;

	public:
		std::vector<Chunk*> GetChunks();
	};
}