#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "tools/crtp.h"

#include "xecs.h"
#include <random>
#include <variant>

#pragma warning (disable:4244)  // Disable bogus VC++ 4.2 conversion warnings. 
#include <GL/gl.h>
#pragma comment (lib, "opengl32.lib") // link with Microsoft OpenGL lib

#define GLUT_STATIC_LIB
#include "GL/glut.h"