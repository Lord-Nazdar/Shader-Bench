#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <memory>
#include <string>

class AssetLoader;

namespace GraphicsInterface {
	void Initialize( GLFWwindow* window, const uint16_t width, const uint16_t height );
	uint16_t CreateShader( const std::string &filname );
	uint16_t CreateProgram( const uint16_t vertexShader, const uint16_t fragmentShader );

	enum UniformType {
		INT1 = 0,
		VEC4 = 2
	};

	uint16_t GetUniformLocation( const std::string name, const UniformType type );
	uint16_t CreateTexture( const std::string &filename );

	uint16_t CreateVertexBuffer( const AssetLoader& asset );
	uint16_t CreateIndexBuffer( const AssetLoader& asset );

	void SetViewport( const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height );

	void BindTexture( const uint8_t stage, const uint16_t location, const uint16_t texture );
	void SubmitDummyDrawcall();
	void SubmitDrawcall( const uint16_t vertexBuffer, const uint16_t indexBuffer, const uint16_t program );

	void SwapBuffers();

	void Shutdown();
}