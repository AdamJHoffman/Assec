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
		virtual const float getCurrentTime() const override;
		virtual const scope<Monitor> getPrimaryMonitor() const override;
		virtual const std::vector<scope<Monitor>> getMonitors() const override;
		virtual ref<Window> createWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn& eventCallBack) override;
	protected:
		virtual void init0() const override;
	};

	const uint32_t toGLFWType(const KEY& key);
	const uint32_t toGLFWType(const MOUSE& button);

	const KEY keyFromGLFWType(const int& key);
	const MOUSE buttonFromGLFWType(const int& button);

} // assec::graphics
