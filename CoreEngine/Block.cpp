#include "stdafx.h"

#include <Block.h>

using namespace BlockNS;

Block::Block(ID _id, bool _isCollidable, bool _isOpaque) : 
	collider(glm::vec3(0)),
	blockID		(_id), 
	isCollidable(_isCollidable), 
	isOpaque	(_isOpaque)
{
	if (_id == ID::Air) faceToDraw = Face::SKIP;

	isDirty = true;
}

Block::~Block()
{

}