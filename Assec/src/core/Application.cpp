#include "acpch.h"

#include <chrono>
#include <thread>

#include "core/Application.h"
#include "input/Input.h"

#include "event/EngineEvents.h"

#include "graphics/WindowManager.h"
#include "graphics/renderer/Renderer.h"

#include "platform/glfw/GLFWWindowContext.h"

#include "util/Profiler.h"
#include "util/Loader.h"
#include "util/PlatformUtils.h"

namespace assec
{
	Application::Application(CONST_REF(std::string) name) : m_Name(name) { TIME_FUNCTION; }
	Application::~Application() { TIME_FUNCTION; }
	void Application::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		input::Input::onEvent(*event);
		this->m_EventQueue->submit(event);
		this->onEvent0(event);
	}
	void Application::handleEvents()
	{
		TIME_FUNCTION;
		if (!graphics::WindowManager::empty())
		{
			for (auto& event : this->m_EventQueue->getEventQueue())
			{
				this->m_LayerStack->onEvent(*event);
				this->m_ActiveScene->onEvent(*event);
			}
		}
		this->m_EventQueue->clear();
		util::FileDialogs::processDialogRequests();
	}
	void Application::init()
	{
		graphics::WindowManager::init(std::make_shared<graphics::GLFWWindowContext>(), [this](ref<events::Event> event) {return this->onEvent(event); });
		util::Profiler::getProfiler().beginSession(this->m_Name);
		TIME_FUNCTION;
		auto videomode = graphics::WindowManager::s_WindowContext->getPrimaryMonitor()->getCurrentVideoMode();
		graphics::WindowManager::addWindow(videomode.width, videomode.height, this->m_Name, nullptr, nullptr);
		graphics::Renderer::init(BATCH_MAX_SIZE, graphics::WindowManager::getMainWindow().getWindowData().graphicsContext->getContextData().m_MaxTextures);
		this->init0();
	}
	void Application::run()
	{
		this->init();
		float lastFrameTime = 0;
		while (!graphics::WindowManager::empty())
		{
			TIME_FUNCTION;
			if (!graphics::WindowManager::getMainWindow().getAttrib(WindowAttribute::ICONIFIED))
			{
				float time = static_cast<float>(graphics::WindowManager::s_WindowContext->getCurrentTime());
				float timeStep = time - lastFrameTime;
				lastFrameTime = time;
				this->onEvent(std::make_shared<events::AppUpdateEvent>(timeStep));
				this->onEvent(std::make_shared<events::AppRenderEvent>(timeStep));
				graphics::WindowManager::prepare();
				this->handleEvents();
				this->run0();
				graphics::WindowManager::finish();
			}
			else
			{
				graphics::WindowManager::s_WindowContext->waitEvents();
			}
			if (this->m_ShouldClose)
			{
				break;
			}
		}
		this->cleanup();
	}
	void Application::close()
	{
		TIME_FUNCTION;
		this->m_ShouldClose = true;
	}
	void Application::cleanup() const
	{
		util::Profiler::getProfiler().endSession();
	}
} // namespace assec
