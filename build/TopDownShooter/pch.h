#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "xecs.h"
#include <random>

#pragma warning (disable:4244)  // Disable bogus VC++ 4.2 conversion warnings. 
#include <GL/gl.h>
#pragma comment (lib, "opengl32.lib") // link with Microsoft OpenGL lib

#endif