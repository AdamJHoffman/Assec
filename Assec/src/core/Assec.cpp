#include "acpch.h"
#include "Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/openGL/OpenGLWindow.h"
#include "graphics/openGL/OpenGLGraphicsContext.h"

void* operator new(size_t size)
{
	assec::util::MemoryManager::getMemoryManager().m_Allocated += (uint32_t)size;
	return malloc(size);
}

void operator delete(void* object, size_t size)
{
	assec::util::MemoryManager::getMemoryManager().m_Freed += (uint32_t)size;
	free(object);
}

namespace assec
{
	ref<graphics::Window> assec::createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, graphics::EventCallBackFn eventCallBack)
	{
		TIME_FUNCTION;
		return std::make_shared<graphics::OpenGLWindow>(width, height, title, monitor, share, eventCallBack);
	}

	void onEvent(events::Event& event)
	{
		TIME_FUNCTION;
		Logger::CORE_LOGGER->getLogger()->info(event.toString());
	}

	void init()
	{
		TIME_FUNCTION;
		util::Profiler::getProfiler().beginSession("ASSEC");
	}

	void cleanup()
	{
		TIME_FUNCTION;
		util::Profiler::getProfiler().endSession();
		glfwTerminate();
	}
}
