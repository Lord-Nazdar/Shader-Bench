#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include "GraphicsInterface.h"
#include <string>
#include <fstream>
#include <iostream>
#define GLM_COORDINATE_SYSTEM GLM_LEFT_HANDED
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>

#include "AssetLoader.h"

void ReloadProgram( uint16_t &program) {
	uint16_t vertexShader = GraphicsInterface::CreateShader( "Shaders/cube.vs", GraphicsInterface::ShaderType::VERTEX_SHADER );
	uint16_t fragmentShader = GraphicsInterface::CreateShader( "Shaders/cube.fs", GraphicsInterface::ShaderType::FRAGMENT_SHADER );
	program = GraphicsInterface::CreateProgram( vertexShader, fragmentShader );
}

int main( int _argc, char** _argv ) {
	uint16_t width = 1280;
	uint16_t height = 720;

	glfwInit();

#ifdef BGFX_Graphics_Interface
	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
#else
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // BGFX_Graphics_Interface

	glfwWindowHint( GLFW_RESIZABLE, false );
	GLFWwindow* window = glfwCreateWindow( width, height, "Shader Bench", NULL, NULL );

	GraphicsInterface::Initialize( window, width, height );

	VertexStructure::init();

	AssetLoader sphere;
	sphere.LoadAsset( "Objects/sphere3.obj" );

	uint16_t vertexBuffer = GraphicsInterface::CreateVertexBuffer(sphere);
	uint16_t indexBuffer = GraphicsInterface::CreateIndexBuffer(sphere);
	
	uint16_t vertexShader = GraphicsInterface::CreateShader( "Shaders/cube.vs", GraphicsInterface::ShaderType::VERTEX_SHADER );
	uint16_t fragmentShader = GraphicsInterface::CreateShader( "Shaders/cube.fs", GraphicsInterface::ShaderType::FRAGMENT_SHADER );
	uint16_t program = GraphicsInterface::CreateProgram( vertexShader, fragmentShader );
	uint16_t normalMapLocation = GraphicsInterface::GetUniformLocation( "s_texNormal", GraphicsInterface::UniformType::INT1 );
	uint16_t normalMapTexture = GraphicsInterface::CreateTexture( "Textures/NormalSphere.png" );

	// Get view matrix
	glm::vec3 up( 0.0f, 0.0f, 1.0f );
	glm::vec3 center( 0.0f, 0.0f, 0.0f );
	glm::vec3 eye( 0.0f, 1.0f, -4.0f );
	glm::mat4 view = glm::lookAt( eye, center, up );

	// Get perspective matrix
	glm::mat4 projection = glm::perspective( glm::radians(60.0f), float( width ) / float( height ), 0.1f, 100.0f );

	GraphicsInterface::SetProjectionViewTransform( view, projection );

	bool key_enterPressed = false;
	do {

		GraphicsInterface::SetViewport( 0, 0, width, height );

		GraphicsInterface::SubmitDummyDrawcall();

		GraphicsInterface::BindTexture( 0, normalMapLocation, normalMapTexture );
		GraphicsInterface::SubmitDrawcall( vertexBuffer, indexBuffer, program );


		GraphicsInterface::SwapBuffers();

		if ( glfwGetKey( window, GLFW_KEY_ENTER ) == GLFW_PRESS && !key_enterPressed) {
			ReloadProgram( program );
			std::cout << "Program reloaded" << std::endl;
			key_enterPressed = true;
		}

		if ( glfwGetKey( window, GLFW_KEY_ENTER ) == GLFW_RELEASE && key_enterPressed ) {
			key_enterPressed = false;
		}

		glfwPollEvents();
	} while ( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( window ) == 0 );

	GraphicsInterface::Shutdown();
	glfwTerminate();
}