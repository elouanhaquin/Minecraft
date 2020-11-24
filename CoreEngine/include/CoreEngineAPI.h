#pragma once

#ifdef COREENGINE_EXPORTS
#define COREENGINE_API __declspec(dllexport)
#else
#define COREENGINE_API __declspec(dllimport)
#endif