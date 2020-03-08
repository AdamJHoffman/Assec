#pragma once
#include "graphics/Window.h"
#include "acpch.h"

namespace assec::graphics
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();
		std::vector<std::shared_ptr<Window>> m_Windows;
		void onEvent(events::Event& event, std::function<void(events::Event&)> function);
	};

}
