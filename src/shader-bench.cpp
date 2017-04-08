#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <bgfx\bgfx.h>
#include <bx\bx.h>
#include <bx\float4x4_t.h>
#include <bgfx\platform.h>
#include "GraphicsInterface.h"
#include <string>
#include <fstream>
#include <iostream>

struct VertexStructure {
	float x, y, z;

	static void init() {
		decl.begin()
			.add( bgfx::Attrib::Position, 3, bgfx::AttribType::Float )
			.end();
	};

	static bgfx::VertexDecl decl;
};

bgfx::VertexDecl VertexStructure::decl;

static VertexStructure s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f },
	{ 1.0f,  1.0f,  1.0f },
	{-1.0f, -1.0f,  1.0f },
	{ 1.0f, -1.0f,  1.0f },
	{-1.0f,  1.0f, -1.0f },
	{ 1.0f,  1.0f, -1.0f },
	{-1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

bgfx::ShaderHandle LoadShader(std::string filename){
	std::ifstream file( filename.c_str(), std::ios::binary );
	std::string s((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	const bgfx::Memory* memory = bgfx::alloc( s.length() );
	memcpy( memory->data, &s[0], s.length() );

	std::cout << s.length() << " : " << s << std::endl;

	return bgfx::createShader( memory );
}

int main( int _argc, char** _argv ) {
	uint16_t width = 1280;
	uint16_t height = 720;

	glfwInit();
	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
	glfwWindowHint( GLFW_RESIZABLE, false );
	GLFWwindow* window = glfwCreateWindow( width, height, "Shader Bench", NULL, NULL );

	GraphicsInterface::Initialize( window, width, height );

	// Create buffers/etc for our cube
	VertexStructure::init();
	bgfx::VertexBufferHandle vertexBuffer = bgfx::createVertexBuffer( bgfx::makeRef( s_cubeVertices, sizeof( s_cubeVertices ) ), VertexStructure::decl );
	bgfx::IndexBufferHandle indexBuffer = bgfx::createIndexBuffer( bgfx::makeRef( s_cubeTriList, sizeof( s_cubeTriList ) ) );

	bgfx::ShaderHandle shader = LoadShader( "Shaders/cube.vs.bin" );
	bgfx::ShaderHandle shader2 = LoadShader( "Shaders/cube.fs.bin" );

	bgfx::ProgramHandle program = bgfx::createProgram( shader, shader2 );


	float at[3]  = { 0.0f, 0.0f,   0.0f };
	float eye[3] = { 0.0f, 0.0f, -35.0f };
	float view[16];
	bx::mtxLookAt(view, eye, at);

	float proj[16];
	bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform( 0, view, proj );

	do {
		bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height) );
		bgfx::touch(0);

		bgfx::setVertexBuffer(vertexBuffer);
		bgfx::setIndexBuffer( indexBuffer );
		bgfx::setState(0
						| BGFX_STATE_DEFAULT
						| BGFX_STATE_PT_TRISTRIP
						);

					// Submit primitive for rendering to view 0.
		bgfx::submit( 0, program );


		bgfx::frame();
		glfwPollEvents();
	} while ( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( window ) == 0 );

	bgfx::shutdown();
	glfwTerminate();
}