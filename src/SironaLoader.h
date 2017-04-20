#pragma once

#include <GLFW\glfw3.h>
#include <gl\GL.h>
#include "glext.h"
#include <assert.h>

// glGentVertexArrays
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

// glBindVertexArray
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

// glEnableVertexAttribArray
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

// glDisableVertexAttribArray
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

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

// glUseProgram
extern PFNGLUSEPROGRAMPROC glUseProgram;

// glGenBuffers
extern PFNGLGENBUFFERSPROC glGenBuffers;

// glBindBuffer
extern PFNGLBINDBUFFERPROC glBindBuffer;

// glBufferData
extern PFNGLBUFFERDATAPROC glBufferData;

// glVertexAttribPointer
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

// glGetUniformLocation
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

// glUniformMatrix4fv
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

// Initialize all GL extensions
void SironaInit();