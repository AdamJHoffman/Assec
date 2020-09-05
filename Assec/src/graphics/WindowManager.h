#pragma once
#include "graphics/Window.h"
#include "graphics/WindowContext.h"
#include "acpch.h"

namespace assec::graphics
{
	class WindowManager
	{
	public:
		~WindowManager();
		static void init(const ref<WindowContext> windowContext, std::function<void(ref<events::Event>)> eventCallBackFn);
		static void prepare();
		static void finish();
		const static bool empty();
		const static void clear();
		const static void addWindow(uint32_t width, uint32_t height, const char* title, Monitor* monitor, Window* share);
		const static void onEvent(ref<events::Event> event);
		static inline std::vector<ref<Window>> getWindows() { TIME_FUNCTION; return m_Windows; }
		static ref<WindowContext> m_WindowContext;
	private:
		WindowManager() {}
		static std::vector<assec::ref<Window>> m_Windows;
		static std::function<void(ref<events::Event>)> m_EventCallBack;
	};

}
