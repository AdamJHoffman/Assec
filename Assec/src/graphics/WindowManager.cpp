#include "acpch.h"

#include "WindowManager.h"

#include "event/WindowEvents.h"

namespace assec::graphics
{
	std::vector<ref<Window>> WindowManager::m_Windows = std::vector<ref<Window>>();
	ref<WindowContext> WindowManager::m_WindowContext = nullptr;
	std::function<void(events::Event*)> WindowManager::m_EventCallBack = nullptr;
	void WindowManager::init(const ref<WindowContext>& windowContext, const std::function<void(events::Event*)>& eventCallBackFn)
	{
		m_WindowContext = windowContext;
		m_EventCallBack = eventCallBackFn;
		TIME_FUNCTION;
		if (!m_WindowContext->m_Initialized)
		{
			m_WindowContext->init();
		}
	}
	WindowManager::~WindowManager()
	{
		TIME_FUNCTION;
		m_WindowContext->cleanup();
	}
	void WindowManager::prepare()
	{
		TIME_FUNCTION;
		for (auto window : m_Windows)
		{
			window->makeCurrent();
			window->clear();
			window->pollEvents();
		}
	}
	void WindowManager::finish()
	{
		TIME_FUNCTION;
		for (auto window : m_Windows)
		{
			window->swapBuffers();
		}
	}
	const bool WindowManager::empty()
	{
		TIME_FUNCTION;
		return m_Windows.empty();
	}
	const void WindowManager::clear()
	{
		TIME_FUNCTION;
		for (auto& window : m_Windows)
		{
			window->clear();
		}
	}
	const Window& WindowManager::addWindow(const uint32_t& width, const uint32_t& height, const char* title, const Monitor* monitor, const Window* share)
	{
		TIME_FUNCTION;
		auto window = m_WindowContext->createWindow(width, height, title, monitor, share, [&](events::Event* event)
			{
				TIME_FUNCTION;
				onEvent(event);
			});
		m_Windows.push_back(window);
		return *m_Windows.back();
	}
	const void WindowManager::onEvent(events::Event* event)
	{
		TIME_FUNCTION;
		events::Dispatcher dispatcher = events::Dispatcher(*event);
		dispatcher.dispatch<events::WindowCloseEvent>([&](const events::WindowCloseEvent& event)
			{
				TIME_FUNCTION;
				m_Windows.erase(std::remove_if(m_Windows.begin(), m_Windows.end(), [](ref<Window> window)
					{
						TIME_FUNCTION;
						return !window->getWindowData().m_Open;
					}), m_Windows.end());
				return false;
			});
		m_EventCallBack(event);
	}
}
