#pragma once

#include <PhysicsEngineAPI.h>
#include <Primitive.h>

namespace PhysicsEngineNS
{
	class PHYSICSENGINE_API AABB : public Primitive
	{
	private:

		glm::vec3 m_pointMin;
		glm::vec3 m_pointMax;

	public:


		AABB(glm::vec3 aPointMin, glm::vec3 aPointMax, glm::vec3 aPosition = glm::vec3(0));

		glm::vec3& GetMinPoint();
		glm::vec3& GetMaxPoint();

	};
}
