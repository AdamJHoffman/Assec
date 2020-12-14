#include "acpch.h"

#include "WindowManager.h"

#include "event/WindowEvents.h"

#include "util/Dispatcher.h"

namespace assec::graphics
{
	std::vector<ref<Window>> WindowManager::m_Windows = std::vector<ref<Window>>();
	ref<WindowContext> WindowManager::s_WindowContext = nullptr;
	std::function<void(ref<events::Event>)> WindowManager::m_EventCallBack = nullptr;
	void WindowManager::init(CONST_REF(ref<WindowContext>) windowContext, CONST_REF(std::function<void(ref<events::Event>)>) eventCallBackFn)
	{
		TIME_FUNCTION;
		s_WindowContext = windowContext;
		m_EventCallBack = eventCallBackFn;
		if (!s_WindowContext->initialized())
		{
			s_WindowContext->init();
		}
	}
	WindowManager::~WindowManager()
	{
		TIME_FUNCTION;
		s_WindowContext->terminate();
	}
	void WindowManager::prepare()
	{
		TIME_FUNCTION;
		for (auto window : m_Windows)
		{
			window->makeContextCurrent();
			window->clear();
		}
		s_WindowContext->pollEvents();
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
	const Window& WindowManager::addWindow(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(std::string) title, const Monitor* monitor, const Window* share)
	{
		TIME_FUNCTION;
		auto window = s_WindowContext->createWindow(width, height, title, monitor, share, [&](ref<events::Event> event)
			{
				onEvent(event);
			});
		m_Windows.push_back(window);
		return *m_Windows.back();
	}
	const void WindowManager::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		util::Dispatcher dispatcher = util::Dispatcher(*event);
		dispatcher.dispatch<events::WindowCloseEvent>([&](const events::WindowCloseEvent& event)
			{
				m_Windows.erase(std::remove_if(m_Windows.begin(), m_Windows.end(), [](ref<Window> window)
					{
						return window->ShouldClose();
					}), m_Windows.end());
				return false;
			});
		m_EventCallBack(event);
	}
} // namespace assec::graphics
