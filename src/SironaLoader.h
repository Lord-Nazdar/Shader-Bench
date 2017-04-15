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

// glDeleteShader
extern PFNGLDELETESHADERPROC glDeleteShader;

// glCreateProgram
extern PFNGLCREATEPROGRAMPROC glCreateProgram;

// glAttachShader
extern PFNGLATTACHSHADERPROC glAttachShader;

// glDetachShader
extern PFNGLDETACHSHADERPROC glDetachShader;

// glLinkProgram
extern PFNGLLINKPROGRAMPROC glLinkProgram;

// glGetProgramiv
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;

// glGetProgramInfoLog
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

// glGenBuffers
extern PFNGLGENBUFFERSPROC glGenBuffers;

// glBindBuffer
extern PFNGLBINDBUFFERPROC glBindBuffer;

// glBufferData
extern PFNGLBUFFERDATAPROC glBufferData;

// Initialize all GL extensions
void SironaInit();