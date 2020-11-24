#pragma once

#ifdef PHYSICSSENGINE_EXPORTS
#define PHYSICSENGINE_API __declspec(dllexport)
#else
#define PHYSICSENGINE_API __declspec(dllimport)
#endif