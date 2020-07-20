#pragma once
#include "Window.h"
#include "Monitor.h"

namespace assec::graphics
{
	class WindowContext
	{
	public:
		virtual ~WindowContext() {}
		virtual void cleanup() const = 0;
		void init()
		{
			this->init0();
			this->m_Initialized = true;
		}
		void cleanup()
		{
			for (auto window : this->m_Windows)
			{
				window->cleanup();
			}
		}
		virtual ref<Monitor> getPrimaryMonitor() const = 0;
		virtual ref<std::vector<ref<Monitor>>> getMonitors() const = 0;
		ref<Window> createWindow(unsigned int width, unsigned int height, const char* title, Monitor* monitor, Window* share, EventCallBackFn eventCallBack)
		{
			auto result = this->createWindow0(width, height, title, monitor, share, eventCallBack);
			this->m_Windows.push_back(result);
			return result;
		}
		bool m_Initialized = false;
	protected:
		WindowContext() {}
		virtual void init0() const = 0;
		virtual ref<Window> createWindow0(unsigned int width, unsigned int height, const char* title, Monitor* monitor, Window* share, EventCallBackFn eventCallBack) = 0;
		std::vector<ref<Window>> m_Windows = std::vector<ref<Window>>();
	};
}
