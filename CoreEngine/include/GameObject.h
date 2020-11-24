#pragma once

#include "stdafx.h"
#include <Component.h>
#include <SphereCollider.h>
#include <Collider.h>
#include <BoxCollider.h>
#include <SphereCollider.h>

namespace CoreEngineNS
{
	class Component;
	class GameObject;

	class GameObject
	{
	protected:
		bool m_active = true;
		std::vector<std::unique_ptr<Component>> m_components;

		ComponentArray m_componentArray;
		ComponentBitSet m_componentBitSet;



	public:

		std::size_t m_colliderID;

		~GameObject() {}

		virtual void FixedUpdate(){}

		virtual void Awake(){}

		virtual void Update()
		{
			for (auto& c : m_components) c->Update();
		}

		virtual void Draw()
		{
			for (auto& c : m_components) c->Draw();
		}

		bool IsActive() const { return m_active; }
		void Destroy() { m_active = false; }

		template<typename T>
		bool HasComponent() const
		{
			return m_componentBitSet[getComponentTypeID<T>()];
		}

		template<typename T, typename ...TArgs>
		T& AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));

			c->m_parent = this;
			std::unique_ptr<Component> cPtr{ c };
			m_components.emplace_back(std::move(cPtr));

			m_componentArray[getComponentTypeID<T>()] = c;
			m_componentBitSet[getComponentTypeID<T>()] = true;

			c->Awake();
			return *c;
		}

		template<typename T> T& GetComponent() const
		{
			auto ptr(m_componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

		Primitive* GetCollider()
		{
			Collider* collider;
			collider = &this->GetComponent<SphereCollider>();
			
			if (collider != nullptr)
				return collider->GetCollider();
				

			collider = &this->GetComponent<BoxCollider>();

			if (collider != nullptr)
				return collider->GetCollider();
		}
	};
}
