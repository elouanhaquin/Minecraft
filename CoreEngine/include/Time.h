#pragma once

#include "CoreEngineAPI.h"
#include <GLFW\glfw3.h>

namespace TimeNS {
	class COREENGINE_API Time
	{

	public:

		static double time;
		static double deltaTime;
		static double fixedDeltaTime;
		static double dayTime;

		static void UpdateTime();

		Time();
		~Time();

	private:

	};
}