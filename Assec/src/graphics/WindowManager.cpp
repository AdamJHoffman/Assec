#include "acpch.h"
#include "WindowManager.h"
#include "core/Core.h"

namespace assec::graphics
{
	WindowManager::WindowManager() : m_Windows(std::vector<std::shared_ptr<Window>>()), m_Events(std::vector<ref<events::Event>>()) {}
	WindowManager::~WindowManager() {}
	void WindowManager::prepare()
	{
		TIME_FUNCTION;
		for (auto window : this->m_Windows)
		{
			window->makeCurrent();
			window->clear();
		}
	}
	void WindowManager::finish()
	{
		TIME_FUNCTION;
		for (auto window : this->m_Windows)
		{
			window->swapBuffers();
			window->pollEvents();
		}
		this->handleEvents();
	}
	const bool WindowManager::empty() const
	{
		TIME_FUNCTION;
		return !this->m_Windows.size();
	}
	const void WindowManager::addWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share)
	{
		TIME_FUNCTION;
		this->m_Windows.push_back(assec::createWindow(width, height, title, monitor, share, [this](std::shared_ptr<events::Event> event)
			{
				TIME_FUNCTION;
				this->addEvent(event);
			}));
	}
	const void WindowManager::addEvent(ref<events::Event> event)
	{
		TIME_FUNCTION;
		this->m_Events.push_back(event);
	}
	void WindowManager::handleEvents()
	{
		TIME_FUNCTION;
		for (auto event : this->m_Events)
		{
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
			assec::onEvent(*event);
		}
		this->m_Events.clear();
	}
}
