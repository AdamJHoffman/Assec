#pragma once

#include "graphics/Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "graphics/Monitor.h"
#include "graphics/openGL/OpenGLGraphicsContext.h"

namespace assec::graphics
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn eventCallBack);
		virtual ~GLFWWindow();
		virtual void setUserPointer() const override;
		virtual void cleanup() const override;
		virtual void validate() const override;
		virtual void makeCurrent() const override;
		virtual void swapBuffers() const override;
		virtual void pollEvents() const override;
		virtual void clear() const override;
		virtual void setSize(const uint32_t& width, const uint32_t& height) const override;
		virtual const glm::vec2 getSize() const override;
		virtual const std::tuple<int, int, int, int> getFrameSize() const override;
		virtual const glm::vec2 getFramebufferSize() const override;
		virtual const glm::vec2 getWindowContentScale() const override;
		virtual void setPosition(const int& x, const int& y) const override;
		virtual const glm::vec2 getPosition() const override;
		virtual void setSizeLimits(const uint32_t& minWidth, const uint32_t& minHeight, const uint32_t& maxWidth, const uint32_t& maxHeight) const override;
		virtual void setAspectRatio(const uint32_t& width, const uint32_t& height) const override;
		virtual void setTitle(const char* title) const override;
		virtual void minimize() const override;
		virtual void restore() const override;
		virtual void maximize() const override;
		virtual void show() const override;
		virtual void hide() const override;
		virtual void focus() const override;
		virtual void requestAttention() const override;
		virtual void setOpacity(const float& opacity) const override;
		virtual const float getOpacity() const override;
		virtual void setSwapInterval(const uint32_t& interval) override;
		virtual const int getKeyState(const int& keycode) const override;
		virtual const int getMouseButtonState(const int& button) const override;
		virtual void setClipboardString(const char* string) const override;
		virtual const char* getClipboardString() const override;
	protected:
		virtual void* createWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share) const override;
		virtual void setupCallbacks() const override;
	};
} // assec::graphics
