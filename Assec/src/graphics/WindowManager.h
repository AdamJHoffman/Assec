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
		void prepare();
		void finish();
		const bool empty() const;
		const void addWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share);
		const void addEvent(std::shared_ptr < events::Event> event);
	private:
		void handleEvents();
		std::vector<std::shared_ptr<events::Event>> m_Events;
		std::vector<std::shared_ptr<Window>> m_Windows;
	};

}
