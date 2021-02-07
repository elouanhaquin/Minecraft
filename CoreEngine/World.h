#pragma once

#include "CoreEngineAPI.h"
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
		void checkNeighboursChunk();
		void Render();
		void Draw();

		uint16_t			   From3Dto1D(uint8_t p_x, uint8_t p_y, uint8_t p_z);
		std::array<uint8_t, 3> From1Dto3D(uint16_t p_index);


	private:

		int worldDimension;
		int worldWidth;
		int worldHeight;

		std::vector<Chunk*> chunks;

		std::atomic<bool>			m_isRunning{ true };
		std::vector<std::thread>	m_chunkLoadThreads;

	public:
		std::vector<Chunk*> GetChunks();
	};
}