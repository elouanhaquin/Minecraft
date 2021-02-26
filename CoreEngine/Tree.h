#pragma once
#include "CoreEngineAPI.h"
#include <Block.h>
#include <glm\glm.hpp>

using namespace BlockNS;
namespace ChunkNS
{
	class COREENGINE_API Tree
	{
	
	public:
		Tree() { ; }
		Tree(glm::ivec3 p_pos);
		~Tree() { ; }
	
		//return the same tree at other pos
		Tree* moveTo(glm::vec3 p_pos);

		glm::vec3  getPos(uint8_t ind)   { return treeBlockPosition[ind]; }
		Block*	   getBlock(uint8_t ind) { return &treeBlocks[ind]; }

	private:
		Block		treeBlocks[9];
		glm::vec3	treeBlockPosition[9];

	};

}