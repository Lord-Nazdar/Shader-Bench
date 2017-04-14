#ifdef Sirona_Graphics_Interface

#include "GraphicsInterface.h"
#include <gl\GL.h>

typedef void (GLAPIENTRY *PFNGENVERTEXARRAYS)(GLsizei n, GLuint *arrays);
PFNGENVERTEXARRAYS glGenVertexArrays = nullptr;

typedef void (GLAPIENTRY *PFNBINDVERTEXARRAYS)(GLuint arrays);
PFNBINDVERTEXARRAYS glBindVertexArray = nullptr;

void GraphicsInterface::Initialize( GLFWwindow* window, const uint16_t width, const uint16_t height ) {
	glfwMakeContextCurrent( window );

	glGenVertexArrays = (PFNGENVERTEXARRAYS) wglGetProcAddress( "glGenVertexArrays" );
	assert( glGenVertexArrays != nullptr );

	glBindVertexArray = (PFNBINDVERTEXARRAYS) wglGetProcAddress( "glBindVertexArray" );
	assert( glBindVertexArray != nullptr );

	GLuint vertexArray;
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );

}

uint16_t GraphicsInterface::CreateShader( const std::string &filname ) {
	return 0;
}

uint16_t GraphicsInterface::CreateProgram( const uint16_t vertexShader, const uint16_t fragmentShader ) {
	return 0;
}

uint16_t GraphicsInterface::GetUniformLocation( const std::string name, const UniformType type ) {
	return 0;
}

uint16_t GraphicsInterface::CreateTexture( const std::string &filename ) {
	return 0;
}

uint16_t GraphicsInterface::CreateVertexBuffer( const AssetLoader& asset ) {
	return 0;
}

uint16_t GraphicsInterface::CreateIndexBuffer( const AssetLoader& asset ) {
	return 0;
}

void GraphicsInterface::SetViewport( const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height ) {

}

void GraphicsInterface::SetProjectionViewTransform( const glm::mat4 &view, const glm::mat4 &projection ) {

}

void GraphicsInterface::SetModelTransform( const glm::mat4 &model ) {

}

void GraphicsInterface::BindTexture( const uint8_t stage, const uint16_t location, const uint16_t texture ) {

}

void GraphicsInterface::SubmitDummyDrawcall() {

}

void GraphicsInterface::SubmitDrawcall( const uint16_t vertexBuffer, const uint16_t indexBuffer, const uint16_t program ) {

}

void GraphicsInterface::SwapBuffers() {

}

void GraphicsInterface::Shutdown() {

}

#endif // Sirona_Graphics_Interface