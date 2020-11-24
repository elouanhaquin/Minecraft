#pragma once

#define PI			3.14159265359f
#define EPSILON		0.00001f

namespace Utils
{
	inline float DegToRad(float aAngleInDegree) { return aAngleInDegree * PI / 180.0f; }
	inline float RadToDeg(float aAngleInRadian) { return aAngleInRadian * 180.0f / PI; }
	const glm::vec3 SphericalToCartesian(float aRadius, float aLongitude, float aColatitude);

	// Comparison functions to avoid float precision error
	inline bool AreEqual(float a, float b) { return abs(a - b) < EPSILON; }
	inline bool AreDifferent(float a, float b) { return !AreEqual(a, b); }
	bool AreEqual(const glm::vec3& v1, const glm::vec3& v2);
	inline bool AreDifferent(const glm::vec3& v1, const glm::vec3& v2) { return !AreEqual(v1, v2); }

	// Min and max redefinition
	template<typename T> inline T Max(T a, T b) { return a < b ? b : a; }
	template<typename T> inline T Max3(T a, T b, T c) { return Max(a, Max(b, c)); }
	template<typename T> inline T Min(T a, T b) { return a < b ? a : b; }
	template<typename T> inline T Min3(T a, T b, T c) { return Min(a, Min(b, c)); }
	template<typename T> inline T Clamp(T a, T aMin, T aMax) { return Min(aMax, Max(a, aMin)); }

	inline float Min3(const glm::vec3& aVec) { return Min3(aVec.x, aVec.y, aVec.z); }
	inline float Max3(const glm::vec3& aVec) { return Max3(aVec.x, aVec.y, aVec.z); }

	template<class T>
	inline T ClampV(const T& aPoint, const T& aPointMin, const T& aPointMax) { return glm::min(aPointMax, glm::max(aPoint, aPointMin)); }
}