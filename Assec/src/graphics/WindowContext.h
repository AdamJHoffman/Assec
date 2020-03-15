#pragma once
#include "Window.h"

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
		ref<Window> createWindow(unsigned int width, unsigned int height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack)
		{
			auto result = this->createWindow0(width, height, title, monitor, share, eventCallBack);
			this->m_Windows.push_back(result);
			return result;
		}
		bool m_Initialized = false;
	protected:
		WindowContext() {}
		virtual void init0() const = 0;
		virtual ref<Window> createWindow0(unsigned int width, unsigned int height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack) = 0;
		std::vector<ref<Window>> m_Windows = std::vector<ref<Window>>();
	};
}