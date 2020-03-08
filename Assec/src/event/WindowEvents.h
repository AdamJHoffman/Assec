#pragma once
#include"Event.h"

namespace assec::events
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(void* window) : Event::Event(window) {}
		~WindowCloseEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowClose);
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(void* window) : Event::Event(window) {}
		~WindowFocusEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowFocus);
	};

	class WindowFocusLostEvent : public Event
	{
	public:
		WindowFocusLostEvent(void* window) : Event::Event(window) {}
		~WindowFocusLostEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowLostFocus);
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(void* window, unsigned int& width, unsigned int& height) : Event::Event(window), m_Width(width), m_Height(height) {}
		~WindowResizeEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowResize);
		unsigned int m_Width, m_Height;
	};

	class WindowContentScaleEvent : public Event
	{
	public:
		WindowContentScaleEvent(void* window, float xscale, float yscale) : Event::Event(window), m_Xscale(xscale), m_Yscale(yscale) {}
		~WindowContentScaleEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowContentScale);
		float m_Xscale, m_Yscale;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(void* window, int& x, int& y) : Event::Event(window), m_X(x), m_Y(y) {}
		~WindowMoveEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowMove);
		unsigned int m_X, m_Y;
	};

	class WindowMinimizeEvent : public Event
	{
	public:
		WindowMinimizeEvent(void* window) : Event::Event(window) {}
		~WindowMinimizeEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowMinimize);
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(void* window) : Event::Event(window) {}
		~WindowMaximizeEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowMaximize);
	};

	class WindowRestoreEvent : public Event
	{
	public:
		WindowRestoreEvent(void* window) : Event::Event(window) {}
		~WindowRestoreEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowRestore);
	};

	class WindowRefreshEvent : public Event
	{
	public:
		WindowRefreshEvent(void* window) : Event::Event(window) {}
		~WindowRefreshEvent() {}
		EVENT_CLASS_TYPE(EventType::WindowRefresh);
	};

}
