#pragma once

typedef uint8_t Block_f;

namespace BlockNS
{
	enum class Face : Block_f
	{
		NOTHING =	0,
		SKIP	=	1	<<	0,

		TOP		=	1	<<	1,
		BOTTOM	=	1	<<	2,
		FRONT	=	1	<<	3,
		BACK	=	1	<<	4,
		RIGHT	=	1	<<	5,
		LEFT	=	1	<<	6,
		ALL		=	TOP | BOTTOM | FRONT | BACK | RIGHT | LEFT,

		NUM_FACES
	};

	using UnderlyingType = std::underlying_type_t<Face>;

	inline Face operator|(const Face _first, const Face _other)
	{
		return (Face)(static_cast<UnderlyingType>(_first) | static_cast<UnderlyingType>(_other));
	}
	inline Face& operator|=( Face& _first, Face _other)
	{
		_first = (Face)(static_cast<UnderlyingType>(_first) | static_cast<UnderlyingType>(_other));
		return _first;
	}

	inline Face operator&(const Face _first, const Face _other)
	{
		return (Face)(static_cast<UnderlyingType>(_first) & static_cast<UnderlyingType>(_other));
	}
	inline Face& operator&=( Face& _first, const Face _other)
	{
		_first = (Face)(static_cast<UnderlyingType>(_first) & static_cast<UnderlyingType>(_other));
		return _first;
	}

	inline Face operator^(const Face _first, const Face _other)
	{
		return (Face)(static_cast<UnderlyingType>(_first) ^ static_cast<UnderlyingType>(_other));
	}
	inline Face& operator^=(Face& _first, const Face _other)
	{
		_first = (Face)(static_cast<UnderlyingType>(_first) ^ static_cast<UnderlyingType>(_other));
		return _first;
	}

	inline Face operator~(const Face _first)
	{
		return (Face)(~static_cast<UnderlyingType>(_first));
	}

	inline std::ostream& operator<<(std::ostream& os, const Face& _other)
	{
		if (_other == Face::ALL)
		{
			os << "ALL";
			return os;
		}

		if (_other == Face::SKIP)
		{
			os << "SKIP";
			return os;
		}
		if ((_other & Face::FRONT) == Face::FRONT)
		{
			os << " | ";
			os << "FRONT";
		}
		if ((_other & Face::BACK) == Face::BACK)
		{
			os << " | ";
			os << "BACK";
		}
		if ((_other & Face::TOP) == Face::TOP)
		{
			os << " | ";
			os << "TOP";
		}
		if ((_other & Face::BOTTOM) == Face::BOTTOM)
		{
			os << " | ";
			os << "BOTTOM";
		}
		if ((_other & Face::RIGHT) == Face::RIGHT)
		{
			os << " | ";
			os << "RIGHT";
		}
		if ((_other & Face::LEFT) == Face::LEFT)
		{
			os << " | ";
			os << "LEFT";
		}
		if (_other == Face::NOTHING)
		{
			os << "NOTHING";
		}

		return os;
	}
}
