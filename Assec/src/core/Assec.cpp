#include "acpch.h"
#include "Config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/openGL/OpenGLWindow.h"
#include "graphics/openGL/OpenGLGraphicsContext.h"

namespace assec
{
	std::shared_ptr<graphics::Window> assec::createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, graphics::EventCallBackFn eventCallBack)
	{
		return std::make_shared<graphics::OpenGLWindow>(width, height, title, monitor, share, eventCallBack);
	}

	void onEvent(events::Event& event)
	{
		Logger::CORE_LOGGER->getLogger()->info(event.toString());
	}

	void init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSetErrorCallback([](int error, const char* message)
			{
				ASSEC_CORE_CRITICAL("GLFW error thrown: error: {0}, message: {1}", error, message);
			});
	}

	void cleanup()
	{
		//glfwTerminate();
	}
}
