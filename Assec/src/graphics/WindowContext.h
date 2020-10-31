#pragma once

#include "Window.h"
#include "Monitor.h"

namespace assec::graphics
{
	class WindowContext
	{
	public:
		virtual ~WindowContext() { TIME_FUNCTION; }
		virtual void cleanup() const = 0;
		void init()
		{
			this->init0();
			this->m_Initialized = true;
		}
		virtual const float getCurrentTime() const = 0;
		virtual const scope<Monitor> getPrimaryMonitor() const = 0;
		virtual const std::vector<scope<Monitor>> getMonitors() const = 0;
		virtual ref<Window> createWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn& eventCallBack) = 0;
		bool m_Initialized = false;
	protected:
		WindowContext() { TIME_FUNCTION; }
		virtual void init0() const = 0;
	};
}
