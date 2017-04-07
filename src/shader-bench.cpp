#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <bgfx\bgfx.h>
#include <bgfx\platform.h>

int main( int _argc, char** _argv ) {
	uint16_t width = 1280;
	uint16_t height = 720;

	glfwInit();
	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
	glfwWindowHint( GLFW_RESIZABLE, false );
	GLFWwindow* window = glfwCreateWindow( width, height, "Shader Bench", NULL, NULL );

	bgfx::PlatformData pd;
	pd.ndt = nullptr;
	pd.nwh = glfwGetWin32Window( window );
	pd.context = nullptr;
	pd.backBuffer = nullptr;
	pd.backBufferDS = nullptr;
	bgfx::setPlatformData( pd );

	bgfx::init();
	bgfx::reset( width, height, BGFX_RESET_VSYNC );

	bgfx::setViewClear( 0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x151515ff );

	do {
		bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height) );
		bgfx::touch(0);
		bgfx::frame();
		glfwPollEvents();
	} while ( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( window ) == 0 );

	bgfx::shutdown();
	glfwTerminate();
}