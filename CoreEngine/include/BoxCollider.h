#pragma once

#include <Collider.h>

namespace CoreEngineNS 
{
	class BoxCollider : public Collider
	{
	private:
		glm::vec3 m_min;
		glm::vec3 m_max;

		glm::vec3 m_minOffset;
		glm::vec3 m_maxOffset;

		AABB* m_box;

	public:
		BoxCollider(glm::vec3 pos, glm::vec3 p_min = glm::vec3(-0.5), glm::vec3 p_max = glm::vec3(0.5));
		//BoxCollider(glm::vec3 p_min, glm::vec3 p_max);
		

		void Awake() override;
		void Update() override;

		inline AABB* getPrimitive() { return m_box; }
	};
}