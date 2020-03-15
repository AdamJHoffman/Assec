#pragma once
#include <glm/glm.hpp>
#include "graphics/GraphicsContext.h"
#include "event/Event.h"

namespace assec::graphics
{
	using EventCallBackFn = std::function<void(ref<events::Event>)>;

	struct WindowData
	{
		WindowData(unsigned int& width, unsigned int& height, const char* title, EventCallBackFn eventCallBack, GraphicsContext* graphicsContext, void* window) : m_Width(width), m_Height(height), m_Title(title), m_Open(true), m_EventCallBack(eventCallBack), m_GraphicsContext(graphicsContext), m_NativeWindow(window), m_SwapInterval(1) { TIME_FUNCTION; }
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
		WindowSizeData(unsigned int& left, unsigned int& top, unsigned int& right, unsigned int& bottom) : m_Left(left), m_Top(top), m_Right(right), m_Bottom(bottom) { TIME_FUNCTION; }
		unsigned int m_Left, m_Top, m_Right, m_Bottom;
	};

	class Window
	{
	public:
		Window(unsigned int& width, unsigned int& height, const char* title, EventCallBackFn& eventCallBack, GraphicsContext* graphicsContext, void* window) : m_WindowData(width, height, title, eventCallBack, graphicsContext, window) { TIME_FUNCTION; }
		virtual ~Window() { TIME_FUNCTION; }
		inline WindowData& getWindowData() const { TIME_FUNCTION; return (WindowData&)this->m_WindowData; }
		virtual const void setUserPointer() const = 0;
		virtual const void cleanup() const = 0;
		virtual const void validate() const = 0;
		virtual const void swapBuffers() const = 0;
		virtual const void pollEvents() const = 0;
		virtual const void makeCurrent() const = 0;

		// --- move to frambuffer perhaps ---
		virtual const void clear() const = 0;

		virtual const void setSize(unsigned int& width, unsigned int& height) const = 0;
		virtual const glm::vec2 getSize() const = 0;
		virtual const std::tuple<int, int, int, int> getFrameSize() const = 0;
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
		virtual const void setSwapInterval(unsigned int& interval) = 0;
		virtual const int getKeyState(int keycode) const = 0;
		virtual const int getMouseButtonState(int button) const = 0;
		virtual const void setClipboardString(const char* string) const = 0;
		virtual const char* getClipboardString() const = 0;
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
		virtual const void setKeyCallback() const = 0;
		virtual const void setCharCallback() const = 0;
		virtual const void setMousePositionCallback() const = 0;
		virtual const void setCursorEnterCallback() const = 0;
		virtual const void setMouseButtonCallback() const = 0;
		virtual const void setMouseScrolledCallback() const = 0;
		virtual const void setPathDropCallback() const = 0;
		WindowData m_WindowData;
	};
}
