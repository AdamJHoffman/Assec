#include "acpch.h"
#include "WindowManager.h"
#include "event/WindowEvents.h"

namespace assec::graphics
{
	std::vector<assec::ref<Window>> WindowManager::m_Windows = std::vector<assec::ref<Window>>();
	ref<WindowContext> WindowManager::m_WindowContext = nullptr;
	std::function<void(ref<events::Event>)> WindowManager::m_EventCallBack = nullptr;
	void WindowManager::init(const ref<WindowContext> windowContext, std::function<void(ref<events::Event>)> eventCallBackFn)
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
	const void WindowManager::addWindow(uint32_t width, uint32_t height, const char* title, Monitor* monitor, Window* share)
	{
		TIME_FUNCTION;
		m_Windows.push_back(m_WindowContext->createWindow(width, height, title, monitor, share, [&](std::shared_ptr<events::Event> event)
			{
				TIME_FUNCTION;
				onEvent(event);
			}));
	}
	const void WindowManager::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		events::Dispatcher dispatcher = events::Dispatcher(*event);
		dispatcher.dispatch<events::WindowCloseEvent>([&](events::WindowCloseEvent& event)
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
