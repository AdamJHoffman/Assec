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

	}

	void cleanup()
	{
		glfwTerminate();
	}
}
