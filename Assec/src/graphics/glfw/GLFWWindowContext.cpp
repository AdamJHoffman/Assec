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
		TIME_FUNCTION;
		glfwTerminate();
	}
	float GLFWWindowContext::getCurrentTime() const
	{
		return static_cast<float>(glfwGetTime());
	}
	ref<Monitor> GLFWWindowContext::getPrimaryMonitor() const
	{
		TIME_FUNCTION;
		return std::make_shared<GLFWMonitor>(glfwGetPrimaryMonitor());
	}
	ref<std::vector<ref<Monitor>>> GLFWWindowContext::getMonitors() const
	{
		TIME_FUNCTION;
		ref<std::vector<ref<Monitor>>> result = std::make_shared<std::vector<ref<Monitor>>>();
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		for (int i = 0; i < count; i++)
		{
			result->push_back(std::make_shared<GLFWMonitor>(GLFWMonitor(monitors[i])));
		}
		return result;
	}
	void GLFWWindowContext::init0() const
	{
		TIME_FUNCTION;
		glfwInit();
	}
	ref<Window> GLFWWindowContext::createWindow0(uint32_t width, uint32_t height, const char* title, Monitor* monitor, Window* share, EventCallBackFn eventCallBack)
	{
		TIME_FUNCTION;
		return std::make_shared<GLFWWindow>(width, height, title, monitor, share, eventCallBack);
	}
}
