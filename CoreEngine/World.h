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
		void Render();
		void Draw();


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