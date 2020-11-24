#pragma once

#include "stdafx.h"
#include <GameObject.h>
#include <Player.h>
#include <RigidBody.h>

namespace CoreEngineNS
{
	class Scene
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::vector<RigidBody*> m_rigidBodies;

	public:
		Scene();
		~Scene();

		const std::vector<std::shared_ptr<GameObject>>& Hierarchy();

		GameObject& AddEntity();

		template<typename  T>
		GameObject& AddGameObject()
		{
			T* e = new T();
			std::unique_ptr<GameObject> ePtr{ e };

			ePtr->AddComponent<Transform>();
			m_gameObjects.emplace_back(std::move(ePtr));
			return *e;
		}

		//TODO
		//GameObject& Cube();

		int Count();

		std::vector<RigidBody*> GetAllRigidBodies();
	};
}