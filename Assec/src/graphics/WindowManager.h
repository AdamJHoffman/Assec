#pragma once
#include "graphics/Window.h"
#include "graphics/WindowContext.h"
#include "acpch.h"

namespace assec::graphics
{
	class WindowManager
	{
	public:
		WindowManager(ref<WindowContext> windowContext, std::function<void(ref<events::Event>)> eventCallBackFn);
		~WindowManager();
		void prepare();
		void finish();
		const bool empty() const;
		const void addWindow(unsigned int width, unsigned int height, const char* title, Monitor* monitor, Window* share);
		const void onEvent(ref<events::Event> event);
		inline std::vector<ref<Window>> getWindows() const { TIME_FUNCTION; return this->m_Windows; }
		ref<WindowContext> m_WindowContext;
	private:
		std::vector<assec::ref<Window>> m_Windows;
		std::function<void(ref<events::Event>)> m_EventCallBack;
	};

}
