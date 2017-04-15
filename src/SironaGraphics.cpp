#ifdef Sirona_Graphics_Interface

#include "GraphicsInterface.h"
#include "SironaLoader.h"
#include "Filesystem.h"
#include <vector>

void GraphicsInterface::Initialize( GLFWwindow* window, const uint16_t width, const uint16_t height ) {
	glfwMakeContextCurrent( window );

	// Init GL extensions
	SironaInit();

	GLuint vertexArray;
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );

}

uint16_t GraphicsInterface::CreateShader( const std::string &filename, const ShaderType type ) {
	// Load the shader from file
	std::string shaderCode = Filesystem::ReadFile( filename );
	char const * shaderSourcePointer = shaderCode.c_str();

	GLuint shaderID = 0;
	shaderID = glCreateShader( type );
	glShaderSource( shaderID, 1, &shaderSourcePointer, nullptr );
	glCompileShader( shaderID );
	
	GLint result;
	int logLength;

	glGetShaderiv( shaderID, GL_COMPILE_STATUS, &result );
	glGetShaderiv( shaderID, GL_INFO_LOG_LENGTH, &logLength );
	if ( logLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(logLength+1);
		glGetShaderInfoLog(shaderID, logLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	return shaderID;
}

uint16_t GraphicsInterface::CreateProgram( const uint16_t vertexShader, const uint16_t fragmentShader ) {
	GLuint programID;
	programID = glCreateProgram();
	
	glAttachShader( programID, vertexShader );
	glAttachShader( programID, fragmentShader );

	glLinkProgram( programID );
	
	GLint result;
	int logLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
	if ( logLength > 0 ){
		std::vector<char> ProgramErrorMessage(logLength+1);
		glGetProgramInfoLog(programID, logLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader( programID, vertexShader );
	glDetachShader( programID, fragmentShader );

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	return programID;
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