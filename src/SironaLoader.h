#pragma once

#include <GLFW\glfw3.h>
#include <gl\GL.h>
#include "glext.h"
#include <assert.h>

// glGentVertexArrays
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

// glBindVertexArray
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

// glCreateShader
extern PFNGLCREATESHADERPROC glCreateShader;

// glShaderSource
extern PFNGLSHADERSOURCEPROC glShaderSource;

// glCompileShader
extern PFNGLCOMPILESHADERPROC glCompileShader;

// glGetShaderiv
extern PFNGLGETSHADERIVPROC glGetShaderiv;

// glGetShaderInfoLog
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

// Initialize all GL extensions
void SironaInit();