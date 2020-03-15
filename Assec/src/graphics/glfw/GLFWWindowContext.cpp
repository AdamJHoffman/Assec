#include "acpch.h"
#include "GLFWWindowContext.h"
#include "graphics/glfw/GLFWWindow.h"
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	GLFWWindowContext::GLFWWindowContext() : WindowContext::WindowContext() {}
	GLFWWindowContext::~GLFWWindowContext() {}
	void GLFWWindowContext::cleanup() const
	{
		glfwTerminate();
	}
	void GLFWWindowContext::init0() const
	{
		glfwInit();
	}
	ref<Window> GLFWWindowContext::createWindow0(unsigned int width, unsigned int height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack)
	{
		return std::make_shared<GLFWWindow>(width, height, title, monitor, share, eventCallBack);
	}
}