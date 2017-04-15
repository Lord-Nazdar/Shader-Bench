#include "SironaLoader.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3native.h>

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexAttribArray = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;

PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;

PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;

PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;

void SironaInit() {
	// Load vertex attrib arrays related functions
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) wglGetProcAddress( "glGenVertexArrays" );
	assert( glGenVertexArrays != nullptr );

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress( "glBindVertexArray" );
	assert( glBindVertexArray != nullptr );

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXARRAYATTRIBPROC) wglGetProcAddress( "glEnableVertexAttribArray" );
	assert( glEnableVertexAttribArray != nullptr );
	
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress( "glDisableVertexAttribArray" );
	assert( glDisableVertexAttribArray != nullptr );

	// Load shader related functions
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress( "glCreateShader" );
	assert( glCreateShader != nullptr );

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress( "glShaderSource" );
	assert( glShaderSource != nullptr );

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress( "glCompileShader" );
	assert( glCompileShader != nullptr );

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress( "glGetShaderiv" );
	assert( glGetShaderiv != nullptr );
	
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress( "glGetShaderInfoLog" );
	assert( glGetShaderInfoLog != nullptr );
	
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress( "glDeleteShader" );
	assert( glDeleteShader != nullptr );

	// Load program related functions
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress( "glCreateProgram" );
	assert( glCreateProgram != nullptr );

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress( "glAttachShader" );
	assert( glAttachShader != nullptr );

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress( "glDetachShader" );
	assert( glDetachShader != nullptr );

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress( "glLinkProgram" );
	assert( glLinkProgram != nullptr );

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress( "glGetProgramiv" );
	assert( glGetProgramiv != nullptr );

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress( "glGetProgramInfoLog" );
	assert( glGetProgramInfoLog != nullptr );

	// Load buffer related functions
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress( "glGenBuffers" );
	assert( glGenBuffers != nullptr );

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress( "glBindBuffer" );
	assert( glBindBuffer != nullptr );

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress( "glBufferData" );
	assert( glBufferData != nullptr );

	// Load draw related functions
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress( "glVertexAttribPointer" );
	assert( glVertexAttribPointer != nullptr );
}
