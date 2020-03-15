#pragma once
#include "graphics/WindowContext.h"

namespace assec::graphics
{
	class GLFWWindowContext : public WindowContext
	{
	public:
		GLFWWindowContext();
		~GLFWWindowContext();
		virtual void cleanup() const override;
	protected:
		virtual void init0() const override;
		virtual ref<Window> createWindow0(unsigned int width, unsigned int height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack) override;
	};
}
