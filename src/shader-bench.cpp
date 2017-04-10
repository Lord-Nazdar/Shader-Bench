#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <bgfx\bgfx.h>
#include <bx\bx.h>
#include <bx\float4x4_t.h>
#include "GraphicsInterface.h"
#include <string>
#include <fstream>
#include <iostream>

#include "AssetLoader.h"

int main( int _argc, char** _argv ) {
	uint16_t width = 1280;
	uint16_t height = 720;

	glfwInit();
	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
	glfwWindowHint( GLFW_RESIZABLE, false );
	GLFWwindow* window = glfwCreateWindow( width, height, "Shader Bench", NULL, NULL );

	GraphicsInterface::Initialize( window, width, height );

	VertexStructure::init();

	AssetLoader sphere;
	sphere.LoadAsset( "Objects/sphere2.obj" );

	uint16_t vertexBuffer = GraphicsInterface::CreateVertexBuffer(sphere);
	uint16_t indexBuffer = GraphicsInterface::CreateIndexBuffer(sphere);
	
	uint16_t vertexShader = GraphicsInterface::CreateShader( "Shaders/cube.vs.bin" );
	uint16_t fragmentShader = GraphicsInterface::CreateShader( "Shaders/cube.fs.bin" );
	uint16_t program = GraphicsInterface::CreateProgram( vertexShader, fragmentShader );
	uint16_t normalMapLocation = GraphicsInterface::GetUniformLocation( "s_texNormal", GraphicsInterface::UniformType::INT1 );
	uint16_t normalMapTexture = GraphicsInterface::CreateTexture( "Textures/NormalSphere.png" );

	float up[3]  = { 0.0f, 0.0f,   1.0f };
	float at[3]  = { 0.0f, 0.0f,   0.0f };
	float eye[3] = { 0.0f, -25.0f, 15.0f };
	float view[16];
	bx::mtxLookAt(view, eye, at, up);

	float proj[16];
	bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform( 0, view, proj );


	do {
		GraphicsInterface::SetViewport( 0, 0, width, height );

		GraphicsInterface::SubmitDummyDrawcall();

		GraphicsInterface::BindTexture( 0, normalMapLocation, normalMapTexture );
		GraphicsInterface::SubmitDrawcall( vertexBuffer, indexBuffer, program );


		GraphicsInterface::SwapBuffers();
		glfwPollEvents();
	} while ( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( window ) == 0 );

	GraphicsInterface::Shutdown();
	glfwTerminate();
}