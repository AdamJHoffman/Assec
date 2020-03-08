#include "acpch.h"
#include "WindowManager.h"
#include "core/Config.h"

namespace assec::graphics
{
	WindowManager::WindowManager() : m_Windows(std::vector<std::shared_ptr<Window>>()), m_Events(std::vector<std::shared_ptr<events::Event>>()) {}
	WindowManager::~WindowManager() {}
	void WindowManager::prepare()
	{
		for (auto window : this->m_Windows)
		{
			window->makeCurrent();
			window->clear();
		}
	}
	void WindowManager::finish()
	{
		for (auto window : this->m_Windows)
		{
			window->swapBuffers();
			window->pollEvents();
		}
		this->handleEvents();
	}
	const bool WindowManager::empty() const
	{
		return !this->m_Windows.size();
	}
	const void WindowManager::addWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share)
	{
		this->m_Windows.push_back(assec::createWindow(width, height, title, monitor, share, [this](std::shared_ptr<events::Event> event)
			{
				this->addEvent(event);
			}));
	}
	const void WindowManager::addEvent(std::shared_ptr<events::Event> event)
	{
		this->m_Events.push_back(event);
	}
	void WindowManager::handleEvents()
	{
		for (auto event : this->m_Events)
		{
			events::Dispatcher dispatcher = events::Dispatcher(*event);
			dispatcher.dispatch<events::WindowCloseEvent>([this](events::WindowCloseEvent& event)
				{
					this->m_Windows.erase(std::remove_if(this->m_Windows.begin(), this->m_Windows.end(), [](std::shared_ptr<Window> window)
						{
							return !window->getWindowData().m_Open;
						}), this->m_Windows.end());
					return false;
				});
			assec::onEvent(*event);
		}
		this->m_Events.clear();
	}
}