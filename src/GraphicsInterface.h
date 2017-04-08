#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <memory>

namespace GraphicsInterface {
	void Initialize( GLFWwindow* window, const uint16_t width, const uint16_t height );
}