#include "SironaLoader.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3native.h>

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

void SironaInit() {
	// Load vertex arrays related functions
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) wglGetProcAddress( "glGenVertexArrays" );
	assert( glGenVertexArrays != nullptr );

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress( "glBindVertexArray" );
	assert( glBindVertexArray != nullptr );

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
}
