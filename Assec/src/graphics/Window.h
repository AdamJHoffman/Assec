#pragma once
#include <glm/glm.hpp>
#include "graphics/GraphicsContext.h"
#include "event/Event.h"

namespace assec::graphics
{
	using EventCallBackFn = std::function<void(events::Event&)>;

	struct WindowData
	{
		WindowData(unsigned int& width, unsigned int& height, const char* title, EventCallBackFn eventCallBack, GraphicsContext* graphicsContext, void* window)
			: m_Width(width), m_Height(height), m_Title(title), m_Open(true), m_EventCallBack(eventCallBack), m_GraphicsContext(graphicsContext), m_NativeWindow(window), m_SwapInterval(1) {}
		unsigned int m_Width, m_Height;
		std::string m_Title;
		bool m_Open;
		EventCallBackFn m_EventCallBack;
		GraphicsContext* m_GraphicsContext;
		void* m_NativeWindow;
		unsigned int m_SwapInterval;
	};

	struct WindowSizeData
	{
		WindowSizeData(unsigned int& left, unsigned int& top, unsigned int& right, unsigned int& bottom) : m_Left(left), m_Top(top), m_Right(right), m_Bottom(bottom) {}
		unsigned int m_Left, m_Top, m_Right, m_Bottom;
	};

	class Window
	{
	public:
		Window(unsigned int& width, unsigned int& height, const char* title, EventCallBackFn& eventCallBack, GraphicsContext* graphicsContext, void* window)
			: m_WindowData(width, height, title, eventCallBack, graphicsContext, window) {}
		virtual ~Window() {}
		inline WindowData& getWindowData() const { return (WindowData&)this->m_WindowData; }
		virtual const void setUserPointer() const = 0;
		virtual const void terminate() const = 0;
		virtual const void validate() const = 0;
		virtual const void swapBuffers() const = 0;
		virtual const void pollEvents() const = 0;
		virtual const void makeCurrent() const = 0;
		// --- move to frambuffer perhaps ---
		virtual const void clear() const = 0;

		virtual const void setSize(unsigned int& width, unsigned int& height) const = 0;
		virtual const glm::vec2 getSize() const = 0;
		virtual const WindowSizeData getFrameSize() const = 0;
		virtual const glm::vec2 getFramebufferSize() const = 0;
		virtual const glm::vec2 getWindowContentScale() const = 0;
		virtual const void setPosition(int& x, int& y) const = 0;
		virtual const glm::vec2 getPosition() const = 0;
		virtual const void setSizeLimits(unsigned int& minWidth, unsigned int& minHeight, unsigned int& maxWidth, unsigned int& maxHeight) const = 0;
		virtual const void setAspectRatio(unsigned int& width, unsigned int& height) const = 0;
		virtual const void setTitle(const char* title) const = 0;
		virtual const void minimize() const = 0;
		virtual const void restore() const = 0;
		virtual const void maximize() const = 0;
		virtual const void show() const = 0;
		virtual const void hide() const = 0;
		virtual const void focus() const = 0;
		virtual const void requestAttention() const = 0;
		virtual const void setOpacity(float opacity) const = 0;
		virtual const float getOpacity() const = 0;
		virtual const void setSwapInterval(unsigned int& interval) const = 0;
	protected:
		virtual void* createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const = 0;
		virtual const void setWindowResizeCallback() const = 0;
		virtual const void setFramebufferResizeCallback() const = 0;
		virtual const void setWindowContentScaleCallback() const = 0;
		virtual const void setCloseCallback() const = 0;
		virtual const void setMinimizeCallback() const = 0;
		virtual const void setMaximizeCallback() const = 0;
		virtual const void setFocusCallback() const = 0;
		virtual const void setRefreshCallback() const = 0;
		virtual const void setPosCallBack() const = 0;
		WindowData m_WindowData;
	};
}
