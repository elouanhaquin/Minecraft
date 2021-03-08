#pragma once

#include <cstdint>

typedef uint8_t Block_t;

namespace BlockNS
{
	enum class ID : Block_t
	{
		Air = 0,
		Grass = 1,
		Wood = 2,
		Stone = 3,
		Sand = 4,
		Iron = 5,
		BedRock = 6,
		Weeds = 7,
		Leaves = 8,
		Water = 9,
		Sun = 10,
		Coal = 11,
		
		
	


		NUM_BLOCK_TYPES
	};
}