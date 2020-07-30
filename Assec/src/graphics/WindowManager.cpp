#include "acpch.h"
#include "WindowManager.h"

namespace assec::graphics
{
	WindowManager::WindowManager(ref<WindowContext> windowContext, std::function<void(ref<events::Event>)> eventCallBackFn) : m_WindowContext(windowContext), m_Windows(std::vector<std::shared_ptr<Window>>()), m_EventCallBack(eventCallBackFn)
	{
		TIME_FUNCTION;
		if (!this->m_WindowContext->m_Initialized)
		{
			this->m_WindowContext->init();
		}
	}
	WindowManager::~WindowManager()
	{
		TIME_FUNCTION;
		this->m_WindowContext->cleanup();
	}
	void WindowManager::prepare()
	{
		TIME_FUNCTION;
		for (auto window : this->m_Windows)
		{
			window->makeCurrent();
			window->clear();
			window->pollEvents();
		}
	}
	void WindowManager::finish()
	{
		TIME_FUNCTION;
		for (auto window : this->m_Windows)
		{
			window->swapBuffers();
		}
	}
	const bool WindowManager::empty() const
	{
		TIME_FUNCTION;
		return this->m_Windows.empty();
	}
	const void WindowManager::addWindow(uint32_t width, uint32_t height, const char* title, Monitor* monitor, Window* share)
	{
		TIME_FUNCTION;
		this->m_Windows.push_back(this->m_WindowContext->createWindow(width, height, title, monitor, share, [this](std::shared_ptr<events::Event> event)
			{
				TIME_FUNCTION;
				this->onEvent(event);
			}));
	}
	const void WindowManager::onEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		events::Dispatcher dispatcher = events::Dispatcher(*event);
		dispatcher.dispatch<events::WindowCloseEvent>([this](events::WindowCloseEvent& event)
			{
				TIME_FUNCTION;
				this->m_Windows.erase(std::remove_if(this->m_Windows.begin(), this->m_Windows.end(), [](ref<Window> window)
					{
						TIME_FUNCTION;
						return !window->getWindowData().m_Open;
					}), this->m_Windows.end());
				return false;
			});
		this->m_EventCallBack(event);
	}
}
