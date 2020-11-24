// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
//CoreEngine
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//Image
#include <SOIL.h>
#include <stb_image.h>

//UI_Text
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

//Assimp
/*
include "assimp/Importer.hpp"
include "assimp/scene.h"
include "assimp/postprocess.h"*/
#include "glm/gtc/matrix_transform.hpp"


// TODO: reference additional headers your program requires here
