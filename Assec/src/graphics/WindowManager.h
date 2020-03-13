#pragma once
#include "graphics/Window.h"
#include "acpch.h"

namespace assec::graphics
{
	class WindowManager
	{
	public:
		WindowManager(std::function<void(events::Event&)> eventCallBackFn);
		~WindowManager();
		void prepare();
		void finish();
		const bool empty() const;
		const void addWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share);
		const void addEvent(ref<events::Event> event);
		inline std::vector<ref<Window>> getWindows() const { return this->m_Windows; }
	private:
		void handleEvents();
		std::vector<assec::ref<events::Event>> m_Events;
		std::vector<assec::ref<Window>> m_Windows;
		std::function<void(events::Event&)> m_EventCallBack;
	};

}
