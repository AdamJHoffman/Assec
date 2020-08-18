﻿#include "acpch.h"

#include "Application.h"
#include "graphics/glfw/GLFWWindowContext.h"
#include "event/EngineEvents.h"

void* operator new(size_t size)
{
	assec::util::MemoryManager::m_Allocated += (uint32_t)size;
	return malloc(size);
}

void operator delete(void* object, size_t size)
{
	assec::util::MemoryManager::m_Freed += (uint32_t)size;
	free(object);
}

namespace assec
{
	Application::Application(const char* name) : AC_WINDOW_MANAGER(std::make_shared<graphics::WindowManager>(std::make_shared<graphics::GLFWWindowContext>(), [this](ref<events::Event> event) {return this->onEvent(event); }))
	{
		util::Profiler::getProfiler().beginSession(name);
	}
	Application::~Application() {}
	const void Application::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		Input::onEvent(*event);
		this->AC_EVENT_QUEUE->m_Events.push_back(event);
	}
	const void Application::handleEvents()
	{
		TIME_FUNCTION;
		if (!this->AC_WINDOW_MANAGER->empty())
		{
			for (auto event : this->AC_EVENT_QUEUE->m_Events)
			{
				AC_CORE_TRACE(event->toString());
				this->AC_LAYER_STACK->onEvent(*event);
				this->m_ActiveScene->reg().view<scene::OrthoCameraComponent>().each([=](auto entity, auto& udc)
					{
						udc.onEvent(*event);
					});
				this->m_ActiveScene->reg().view<scene::NativeScriptComponent>().each([=](auto entity, auto& nsc)
					{
						if (!nsc.m_Instance)
						{
							nsc.m_InstantiateFunction(entity, this->m_ActiveScene.get());
						}
						nsc.onEvent(*event);
					});
			}
		}
		this->AC_EVENT_QUEUE->m_Events.clear();
	}
	const void Application::run()
	{
		this->AC_WINDOW_MANAGER->addWindow(1920, 1080, "Assec", nullptr, nullptr);
		this->init();
		float lastFrameTime = 0;
		while (!this->AC_WINDOW_MANAGER->empty())
		{
			TIME_FUNCTION;
			float time = this->AC_WINDOW_MANAGER->m_WindowContext->getCurrentTime();
			float timeStep = time - lastFrameTime;
			lastFrameTime = time;
			this->onEvent(std::make_shared<events::AppUpdateEvent>(timeStep));
			this->onEvent(std::make_shared<events::AppRenderEvent>(timeStep));
			this->AC_WINDOW_MANAGER->prepare();
			this->handleEvents();
			this->AC_WINDOW_MANAGER->finish();
			if (this->m_ShouldClose)
			{
				break;
			}
		}
		this->cleanup();
	}
	void Application::close()
	{
		this->m_ShouldClose = true;
	}
} // namespace assec
