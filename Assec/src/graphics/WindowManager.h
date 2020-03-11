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
		const void addEvent(ref<events::Event> event);
	private:
		void handleEvents();
		std::vector<assec::ref<events::Event>> m_Events;
		std::vector<assec::ref<Window>> m_Windows;
	};

}
