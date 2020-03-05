#include <acpch.h>
#include "Config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <graphics/openGL/OpenGLWindow.h>

namespace assec
{
	static Logger CORE_LOGGER = Logger("CORE");

	void init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		unsigned int width = 1920, height = 1080;

		std::shared_ptr<Window> window = std::make_shared<OpenGLWindow>((unsigned int&) width, (unsigned int&) height, "Assec Engine", nullptr, nullptr);

		while (!glfwWindowShouldClose((GLFWwindow*)(window->getWindow())))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			window->swapBuffers();
			window->pollEvents();
		}


	}

	void cleanup()
	{

	}
}