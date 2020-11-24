#pragma once

#include "stdafx.h"

#include <Component.h>

namespace CoreEngineNS
{
	class Transform : public Component
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_scale;
		int m_oldPositionY;

	public:
		Transform();
		~Transform();

		const glm::vec3& GetPosition() const;
		const glm::vec3& GetForward() const;
		const glm::vec3& GetScale() const;
		//int& GetOldPositionY();


		void SetPosition(const glm::vec3& p_position);
		void SetPositionX(const float& p_x);
		void SetPositionY(const float& p_y);
		void SetPositionZ(const float& p_z);
		void SetForward(const glm::vec3& p_forward);
		void SetScale(const glm::vec3& p_scale);
	};

}