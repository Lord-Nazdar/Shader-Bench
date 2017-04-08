#ifdef BGFX_Graphics_Interface

#include "GraphicsInterface.h"
#include <bgfx\bgfx.h>
#include <bgfx\platform.h>

void GraphicsInterface::Initialize( GLFWwindow* window, const uint16_t width, const uint16_t height ){
	bgfx::PlatformData pd;
	pd.ndt = nullptr;
	pd.nwh = glfwGetWin32Window( window );
	pd.context = nullptr;
	pd.backBuffer = nullptr;
	pd.backBufferDS = nullptr;
	bgfx::setPlatformData( pd );

	bgfx::init( bgfx::RendererType::OpenGL );
	bgfx::reset( width, height, BGFX_RESET_VSYNC );

	bgfx::setViewClear( 0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x151515ff );
}

#endif // BGFX_Graphics_Interface