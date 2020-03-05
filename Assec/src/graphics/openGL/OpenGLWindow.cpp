#include <acpch.h>
#include "OpenGLWindow.h"

namespace assec
{
	OpenGLWindow::OpenGLWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) 
		: Window::Window(width, height, title, this->createWindow(width, height, title, monitor, share)) 
	{
		if (this->getWindow() == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		this->makeCurrent();
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
	}
	OpenGLWindow::~OpenGLWindow() 
	{
		glfwDestroyWindow((GLFWwindow*)this->getWindow());
	}
	const void OpenGLWindow::makeCurrent() const
	{
		glfwMakeContextCurrent((GLFWwindow*)this->getWindow());
	}
	const void OpenGLWindow::swapBuffers() const
	{
		glfwSwapBuffers((GLFWwindow*)this->getWindow());
	}
	const void OpenGLWindow::pollEvents() const
	{
		glfwPollEvents();
	}
	void* OpenGLWindow::createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const
	{
		return glfwCreateWindow(width, height, title, (GLFWmonitor*)monitor, (GLFWwindow*)share);
	}
}