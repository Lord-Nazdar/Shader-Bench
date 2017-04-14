#ifdef BGFX_Graphics_Interface

#include "GraphicsInterface.h"
#include <bgfx\bgfx.h>
#include <bgfx\platform.h>
#include <vector>
#include <assert.h>
#include <lodepng.h>
#include "Filesystem.h"
#include "AssetLoader.h"

void GraphicsInterface::Initialize( GLFWwindow* window, const uint16_t width, const uint16_t height ) {
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

uint16_t GraphicsInterface::CreateShader( const std::string &filename ) {
	std::string shaderCode = Filesystem::ReadFile( filename );
	const bgfx::Memory* memory = bgfx::copy( &shaderCode[0], shaderCode.length() );

	return bgfx::createShader( memory ).idx;
}

uint16_t GraphicsInterface::CreateProgram( const uint16_t vertexShader, const uint16_t fragmentShader ) {
	bgfx::ShaderHandle h_vertexShader = { vertexShader };
	bgfx::ShaderHandle h_fragmentShader = { fragmentShader };

	return bgfx::createProgram( h_vertexShader, h_fragmentShader ).idx;
}

uint16_t GraphicsInterface::GetUniformLocation( const std::string name, const UniformType type ) {
	bgfx::UniformType::Enum uniformType = static_cast<bgfx::UniformType::Enum>(static_cast<int>(type));
	return bgfx::createUniform( name.c_str(), uniformType ).idx;
}

uint16_t GraphicsInterface::CreateTexture( const std::string & filename ) {
	std::vector<unsigned char> pixels;
	unsigned width, height;

	unsigned error = lodepng::decode( pixels, width, height, filename );
	assert( !error );

	const bgfx::Memory* memory = bgfx::copy( &pixels[0], pixels.size() * sizeof( unsigned char ) );
	bgfx::TextureHandle texture = bgfx::createTexture2D( width, height, false, 1, bgfx::TextureFormat::RGBA8, 0U, memory );

	return texture.idx;
}

uint16_t GraphicsInterface::CreateVertexBuffer( const AssetLoader & asset ) {
	uint16_t index = bgfx::createVertexBuffer( bgfx::makeRef( &asset.AssetVertexData[0], asset.AssetVertexData.size() * sizeof( VertexStructure ) ), VertexStructure::decl ).idx;
	return index;
}

uint16_t GraphicsInterface::CreateIndexBuffer( const AssetLoader & asset ) {
	uint16_t index = bgfx::createIndexBuffer( bgfx::makeRef( &asset.Indices[0], asset.Indices.size() * sizeof( uint32_t ) ), BGFX_BUFFER_INDEX32 ).idx;
	return index;
}

void GraphicsInterface::SetViewport( const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height ) {
	bgfx::setViewRect( 0, x, y, width, height );
}


void GraphicsInterface::SetProjectionViewTransform( const glm::mat4 & view, const glm::mat4 & projection ) {
	bgfx::setViewTransform( 0, &view, &projection );
}

void GraphicsInterface::SetModelTransform( const glm::mat4 & model ) {
	bgfx::setTransform( &model );
}

void GraphicsInterface::BindTexture( const uint8_t stage, const uint16_t location, const uint16_t texture ) {
	bgfx::setTexture( stage, bgfx::UniformHandle{ location }, bgfx::TextureHandle{ texture } );
}

void GraphicsInterface::SubmitDummyDrawcall() {
	bgfx::touch( 0 );
}

void GraphicsInterface::SubmitDrawcall( const uint16_t vertexBuffer, const uint16_t indexBuffer, const uint16_t program ) {
	bgfx::setVertexBuffer( bgfx::VertexBufferHandle{ vertexBuffer } );
	bgfx::setIndexBuffer( bgfx::IndexBufferHandle{ indexBuffer } );
	bgfx::setState( 0 | BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_MSAA
	);

	bgfx::submit( 0, bgfx::ProgramHandle{ program } );
}

void GraphicsInterface::SwapBuffers() {
	bgfx::frame();
}

void GraphicsInterface::Shutdown() {
	bgfx::shutdown();
}

#endif // BGFX_Graphics_Interface