#pragma once

#include "stdafx.h"

namespace CoreEngineNS
{
	class Component;
	class GameObject;
	
	using ComponentID = std::size_t;
	constexpr  std::size_t maxComponents = 32;
	using ComponentBitSet = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

	inline ComponentID getComponentTypeID()
	{
		static ComponentID lastID = 0u;
		return lastID++;
	}

	template<typename T>
	ComponentID getComponentTypeID() noexcept
	{
		static ComponentID typeID = getComponentTypeID();
		return typeID;
	}

	class Component
	{
	public:
		GameObject* m_parent;

		virtual void Awake() {}
		virtual void Update() {}
		virtual void Draw() {}

		virtual ~Component() {}
	};
}