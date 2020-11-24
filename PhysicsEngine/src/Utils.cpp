#include "stdafx.h"

#include <Utils.h>

namespace Utils
{
	const glm::vec3 SphericalToCartesian(float aRadius, float aLongitude, float aColatitude)
	{
		const float theta = DegToRad(aLongitude);
		const float phi = DegToRad(aColatitude);
		const float sinPhi = sin(phi);
		return glm::vec3(
			aRadius * sinPhi * sin(theta),
			aRadius * cos(phi),
			aRadius * sinPhi * cos(theta)
		);
	}

	bool AreEqual(const glm::vec3& v1, const glm::vec3& v2)
	{
		int i = 0;
		while ((i < 3) && AreEqual(v1[i], v2[i]))
		{
			++i;
		}
		return (i == 3);
	}
}