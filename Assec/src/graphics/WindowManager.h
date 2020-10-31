#pragma once

#include "graphics/Window.h"
#include "graphics/WindowContext.h"

namespace assec::graphics
{
	class WindowManager
	{
	public:
		~WindowManager();
		static void init(const ref<WindowContext>& windowContext, const std::function<void(events::Event*)>& eventCallBackFn);
		static void prepare();
		static void finish();
		const static bool empty();
		const static void clear();
		const static Window& addWindow(const uint32_t& width, const uint32_t& height, const char* title, const Monitor* monitor, const Window* share);
		const static void onEvent(events::Event* event);
		static inline std::vector<ref<Window>> getWindows() { TIME_FUNCTION; return m_Windows; }
		static ref<WindowContext> m_WindowContext;
	private:
		WindowManager() {}
		static std::vector<ref<Window>> m_Windows;
		static std::function<void(events::Event*)> m_EventCallBack;
	};

}
