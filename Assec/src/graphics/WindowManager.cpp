#include "acpch.h"
#include "WindowManager.h"

namespace assec::graphics
{
	WindowManager::WindowManager() : m_Windows(std::vector<std::shared_ptr<Window>>()) {}
	WindowManager::~WindowManager() {}
	void WindowManager::onEvent(events::Event& event, std::function<void(events::Event&)> function)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::WindowCloseEvent>([this](events::WindowCloseEvent& event)
			{
				std::remove_if(this->m_Windows.begin(), this->m_Windows.end(), [](std::shared_ptr<Window> window)
					{
						return window == NULL;
					});
				return false;
			});
		function(event);
	}
}