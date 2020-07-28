#pragma once
#include "graphics/WindowContext.h"
#include "GLFWMonitor.h"

namespace assec::graphics
{
	class GLFWWindowContext : public WindowContext
	{
	public:
		GLFWWindowContext();
		~GLFWWindowContext();
		virtual void cleanup() const override;
		virtual float getCurrentTime() const override;
		virtual ref<Monitor> getPrimaryMonitor() const override;
		virtual ref<std::vector<ref<Monitor>>> getMonitors() const override;
	protected:
		virtual void init0() const override;
		virtual ref<Window> createWindow0(unsigned int width, unsigned int height, const char* title, Monitor* monitor, Window* share, EventCallBackFn eventCallBack) override;
	};
}
