#pragma once
#include"Event.h"

namespace assec::events
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowCloseEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowClose);
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowFocusEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowFocus);
	};

	class WindowFocusLostEvent : public Event
	{
	public:
		WindowFocusLostEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowFocusLostEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowLostFocus);
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(void* window, uint32_t& width, uint32_t& height) : Event::Event(window), m_Width(width), m_Height(height) { TIME_FUNCTION; }
		~WindowResizeEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowResize);
		uint32_t m_Width, m_Height;
	};

	class WindowContentScaleEvent : public Event
	{
	public:
		WindowContentScaleEvent(void* window, float xscale, float yscale) : Event::Event(window), m_Xscale(xscale), m_Yscale(yscale) { TIME_FUNCTION; }
		~WindowContentScaleEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowContentScale);
		float m_Xscale, m_Yscale;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(void* window, int& x, int& y) : Event::Event(window), m_X(x), m_Y(y) { TIME_FUNCTION; }
		~WindowMoveEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowMove);
		uint32_t m_X, m_Y;
	};

	class WindowMinimizeEvent : public Event
	{
	public:
		WindowMinimizeEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowMinimizeEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowMinimize);
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowMaximizeEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowMaximize);
	};

	class WindowRestoreEvent : public Event
	{
	public:
		WindowRestoreEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowRestoreEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowRestore);
	};

	class WindowRefreshEvent : public Event
	{
	public:
		WindowRefreshEvent(void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowRefreshEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::WindowRefresh);
	};

}
