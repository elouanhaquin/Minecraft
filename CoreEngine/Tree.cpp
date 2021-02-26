#include "stdafx.h"
#include "Tree.h"

ChunkNS::Tree::Tree(glm::ivec3 p_pos)
{
	treeBlocks[0] = Block(ID::Wood, true, true);
	treeBlocks[1] = Block(ID::Wood, true, true);
	treeBlocks[2] = Block(ID::Wood, true, true);
	treeBlocks[3] = Block(ID::Leaves, true, true);
	treeBlocks[4] = Block(ID::Leaves, true, true);
	treeBlocks[5] = Block(ID::Leaves, true, true);
	treeBlocks[6] = Block(ID::Leaves, true, true);
	treeBlocks[7] = Block(ID::Leaves, true, true);
	treeBlocks[8] = Block(ID::Leaves, true, true);


	treeBlockPosition[0] = glm::ivec3(p_pos.x, p_pos.y, p_pos.z);
	treeBlockPosition[1] = glm::ivec3(p_pos.x, p_pos.y + 1, p_pos.z);
	treeBlockPosition[2] = glm::ivec3(p_pos.x, p_pos.y + 2, p_pos.z);
	treeBlockPosition[3] = glm::ivec3(p_pos.x, p_pos.y + 3, p_pos.z);
	treeBlockPosition[4] = glm::ivec3(p_pos.x + 1, p_pos.y + 3, p_pos.z);
	treeBlockPosition[5] = glm::ivec3(p_pos.x - 1, p_pos.y + 3, p_pos.z);
	treeBlockPosition[6] = glm::ivec3(p_pos.x, p_pos.y + 4, p_pos.z);
	treeBlockPosition[7] = glm::ivec3(p_pos.x, p_pos.y + 3, p_pos.z - 1);
	treeBlockPosition[8] = glm::ivec3(p_pos.x, p_pos.y + 3, p_pos.z + 1);
}


