#pragma once

#include <cstdint>

typedef uint8_t Block_t;

namespace BlockNS
{
	enum class ID : Block_t
	{
		Air = 0,
		Grass = 1,
		Coal = 2,
		Sand = 3,
		Stone = 4,
		BedRock = 5,

		NUM_BLOCK_TYPES
	};
}