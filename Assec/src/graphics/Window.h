#pragma once

#include <glm/glm.hpp>

#include "graphics/GraphicsContext.h"
#include "graphics/Monitor.h"

#include "event/Event.h"

namespace assec::graphics
{
	using EventCallBackFn = std::function<void(events::Event*)>;

	struct WindowData
	{
		WindowData(const uint32_t& width, const uint32_t& height, const std::string& title, const EventCallBackFn eventCallBack, const GraphicsContext* graphicsContext, const void* window) : m_Width(width), m_Height(height), m_Title(title), m_Open(true), m_EventCallBack(eventCallBack), m_GraphicsContext(graphicsContext), m_NativeWindow(window), m_SwapInterval(1) { TIME_FUNCTION; }
		uint32_t m_Width, m_Height;
		std::string m_Title;
		bool m_Open;
		EventCallBackFn m_EventCallBack;
		const GraphicsContext* m_GraphicsContext;
		const void* m_NativeWindow;
		uint32_t m_SwapInterval;
	};

	class Window
	{
	public:
		Window(const uint32_t& width, const uint32_t& height, const std::string& title, const EventCallBackFn& eventCallBack, const GraphicsContext* graphicsContext, const void* window) : m_WindowData(width, height, title, eventCallBack, graphicsContext, window) { TIME_FUNCTION; }
		virtual ~Window() { TIME_FUNCTION; }
		inline WindowData& getWindowData() const { TIME_FUNCTION; return (WindowData&)this->m_WindowData; }
		virtual void setUserPointer() const = 0;
		virtual void cleanup() const = 0;
		virtual void validate() const = 0;
		virtual void swapBuffers() const = 0;
		virtual void pollEvents() const = 0;
		virtual void makeCurrent() const = 0;

		// --- move to frambuffer perhaps ---
		virtual void clear() const = 0;

		virtual void setSize(const uint32_t& width, const uint32_t& height) const = 0;
		virtual const glm::vec2 getSize() const = 0;
		virtual const std::tuple<int, int, int, int> getFrameSize() const = 0;
		virtual const glm::vec2 getFramebufferSize() const = 0;
		virtual const glm::vec2 getWindowContentScale() const = 0;
		virtual void setPosition(const int& x, const int& y) const = 0;
		virtual const glm::vec2 getPosition() const = 0;
		virtual void setSizeLimits(const uint32_t& minWidth, const uint32_t& minHeight, const uint32_t& maxWidth, const uint32_t& maxHeight) const = 0;
		virtual void setAspectRatio(const uint32_t& width, const uint32_t& height) const = 0;
		virtual void setTitle(const char* title) const = 0;
		virtual void minimize() const = 0;
		virtual void restore() const = 0;
		virtual void maximize() const = 0;
		virtual void show() const = 0;
		virtual void hide() const = 0;
		virtual void focus() const = 0;
		virtual void requestAttention() const = 0;
		virtual void setOpacity(const float& opacity) const = 0;
		virtual const float getOpacity() const = 0;
		virtual void setSwapInterval(const uint32_t& interval) = 0;
		virtual const int getKeyState(const int& keycode) const = 0;
		virtual const int getMouseButtonState(const int& button) const = 0;
		virtual void setClipboardString(const char* string) const = 0;
		virtual const char* getClipboardString() const = 0;
	protected:
		virtual void* createWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share) const = 0;
		virtual void setupCallbacks() const = 0;
		WindowData m_WindowData;
	};
}
