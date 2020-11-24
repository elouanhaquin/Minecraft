// Console.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <CoreEngine.h>

using namespace CoreEngineNS;

int main()
{
	std::cout << "Console Alive" << std::endl;

	{
		CoreEngine engine;

		engine.IgniteRenderEngine(1280, 720, false);
		engine.IgnitePhysicsEngine();
		engine.Run();
	}
	
	system("pause");
    return 0;
}

