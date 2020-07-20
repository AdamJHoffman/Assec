﻿#include "acpch.h"
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
	ref<Monitor> GLFWWindowContext::getPrimaryMonitor() const
	{
		return std::make_shared<GLFWMonitor>(glfwGetPrimaryMonitor());
	}
	ref<std::vector<ref<Monitor>>> GLFWWindowContext::getMonitors() const
	{
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
		glfwInit();
	}
	ref<Window> GLFWWindowContext::createWindow0(unsigned int width, unsigned int height, const char* title, Monitor* monitor, Window* share, EventCallBackFn eventCallBack)
	{
		return std::make_shared<GLFWWindow>(width, height, title, monitor, share, eventCallBack);
	}
}