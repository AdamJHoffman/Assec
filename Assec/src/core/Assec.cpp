#include "acpch.h"
#include "Core.h"
#include "graphics/glfw/GLFWWindowContext.h"
#include "graphics/openGL/OpenGLGraphicsContext.h"

#include "graphics/openGL/OpenGLBuffer.h"
#include "graphics/openGL/OpenGLVertexArray.h"


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
	Assec::Assec() : AC_WINDOW_MANAGER(std::make_shared<graphics::WindowManager>(std::make_shared<graphics::GLFWWindowContext>(), [this](ref<events::Event> event) {return this->onEvent(event); })), AC_LAYER_STACK(std::make_shared<layersystem::LayerStack>()), AC_EVENT_QUEUE(std::make_shared<events::EventQueue>()), AC_INPUT_MANAGER(std::make_shared<InputManager>())
	{
		util::Profiler::getProfiler().beginSession("ASSEC");
	}
	Assec::~Assec()
	{
		util::Profiler::getProfiler().endSession();
	}
	void Assec::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		this->AC_INPUT_MANAGER->onEvent(*event);
		this->AC_EVENT_QUEUE->m_Events.push_back(event);
	}
	void Assec::handleEvents()
	{
		TIME_FUNCTION;
		for (auto event : AC_EVENT_QUEUE->m_Events)
		{
			AC_CORE_TRACE(event->toString());
			AC_LAYER_STACK->onEvent(*event);
		}
		AC_EVENT_QUEUE->m_Events.clear();
	}
}
