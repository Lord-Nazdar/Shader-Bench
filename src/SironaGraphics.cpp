#ifdef Sirona_Graphics_Interface

#include "GraphicsInterface.h"
#include "SironaLoader.h"
#include "Filesystem.h"
#include "AssetLoader.h"
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
	// Prepare vx data
	/// TODO: Optimize that by changing input structure
	std::vector<glm::vec3> vertexData;
	for ( auto data : asset.AssetVertexData ) {
		vertexData.push_back( glm::vec3{ data.x, data.y, data.z } );
	}

	GLuint vertexBufferID = 0;
	glGenBuffers( 1, &vertexBufferID );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glBufferData( GL_ARRAY_BUFFER, vertexData.size() * sizeof( glm::vec3 ), &vertexData[0], GL_STATIC_DRAW );

	return vertexBufferID;
}

uint16_t GraphicsInterface::CreateIndexBuffer( const AssetLoader& asset ) {
	GLuint indexBufferID = 0;
	glGenBuffers( 1, &indexBufferID );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBufferID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, asset.Indices.size() * sizeof( uint32_t ), &asset.Indices[0], GL_STATIC_DRAW );

	return indexBufferID;
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
	glBindVertexArray( 0 );
}

void GraphicsInterface::SubmitDrawcall( const uint16_t vertexBuffer, const uint16_t indexBuffer, const uint16_t program, const AssetLoader& asset ) {
	glClear( GL_COLOR_BUFFER_BIT );
	
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
	glDrawElements( GL_TRIANGLES, asset.Indices.size(), GL_UNSIGNED_INT, nullptr );
}

void GraphicsInterface::SwapBuffers( GLFWwindow* window ) {
	glDisableVertexAttribArray( 0 );

	glfwSwapBuffers( window );
}

void GraphicsInterface::Shutdown() {

}

#endif // Sirona_Graphics_Interface