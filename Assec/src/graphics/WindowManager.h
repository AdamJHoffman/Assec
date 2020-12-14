#pragma once

#include "graphics/Window.h"
#include "graphics/WindowContext.h"

namespace assec::graphics
{
	class WindowManager
	{
	public:
		~WindowManager();
		static void init(CONST_REF(ref<WindowContext>) windowContext, CONST_REF(std::function<void(ref<events::Event>)>) eventCallBackFn);
		static void prepare();
		static void finish();
		const static bool empty();
		const static void clear();
		const static Window& addWindow(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(std::string) title, const Monitor* monitor, const Window* share);
		const static void onEvent(ref<events::Event> event);
		static inline std::vector<ref<Window>> getWindows() { TIME_FUNCTION; return m_Windows; }
		static REF(Window) getMainWindow() 
		{ 
			TIME_FUNCTION;  
			if (!m_Windows.empty())
			{
				return *m_Windows[0];
			}
			return *((Window*)nullptr);
		}
		static ref<WindowContext> s_WindowContext;
	private:
		WindowManager() { TIME_FUNCTION; }
		static std::vector<ref<Window>> m_Windows;
		static std::function<void(ref<events::Event>)> m_EventCallBack;
	};

}
