#include "acpch.h"

#include "Application.h"
#include "Input.h"

#include "graphics/glfw/GLFWWindowContext.h"
#include "graphics/WindowManager.h"
#include "graphics/renderer/Renderer.h"

#include "event/EngineEvents.h"

#include "util/Profiler.h"
#include "util/Loader.h"
#include "util/PlatformUtils.h"

namespace assec
{
	Application::Application(const std::string name)
	{
		graphics::WindowManager::init(std::make_shared<graphics::GLFWWindowContext>(), [this](ref<events::Event> event) {return this->onEvent(event); });
		util::Profiler::getProfiler().beginSession(name);
	}
	Application::~Application() {}
	void Application::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		Input::onEvent(*event);
		this->AC_EVENT_QUEUE->submit(event);
	}
	void Application::handleEvents()
	{
		TIME_FUNCTION;
		if (!graphics::WindowManager::empty())
		{
			for (auto& event : this->AC_EVENT_QUEUE->getEventQueue())
			{
				AC_CORE_TRACE(event->toString());
				this->AC_LAYER_STACK->onEvent(event);
				this->m_ActiveScene->onEvent(event);
			}
		}
		this->AC_EVENT_QUEUE->clear();
		util::FileDialogs::processDialogRequests();
	}
	void Application::run()
	{
		auto videomode = graphics::WindowManager::m_WindowContext->getPrimaryMonitor()->m_CurrentVideoMode;
		auto& window = graphics::WindowManager::addWindow(videomode.m_Width, videomode.m_Height, "Assec", nullptr, nullptr);
		graphics::Renderer::init(BATCH_MAX_SIZE, window.getWindowData().m_GraphicsContext->getContextData().m_MaxTextures);
		this->init();
		float lastFrameTime = 0;
		while (!graphics::WindowManager::empty())
		{
			TIME_FUNCTION;
			if (!window.isMinimized())
			{
				float time = graphics::WindowManager::m_WindowContext->getCurrentTime();
				float timeStep = time - lastFrameTime;
				lastFrameTime = time;
				this->onEvent(std::make_shared<events::AppUpdateEvent>(timeStep));
				this->onEvent(std::make_shared<events::AppRenderEvent>(timeStep));
			}
			graphics::WindowManager::prepare();
			this->handleEvents();
			graphics::WindowManager::finish();
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
	void Application::cleanup() const
	{
		delete this->AC_LAYER_STACK;
		delete this->AC_EVENT_QUEUE;
		util::Profiler::getProfiler().endSession();
	}
} // namespace assec
