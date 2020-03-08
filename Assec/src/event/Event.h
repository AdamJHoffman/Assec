#pragma once

#include "acpch.h"

namespace assec::events
{

#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return  type;}\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* toString() const override { return #type; }

	enum class EventType
	{
		None = 0,
		WindowClose, WindowFocus, WindowLostFocus, WindowResize, WindowContentScale, WindowMove, WindowMinimize, WindowMaximize, WindowRestore, WindowRefresh,
		AppTick, AppUpdate, AppRender, PathDropped,
		KeyPressed, KeyReleased, KeyRepeated, CharTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, CursorEntered, CursorExited
	};

	class Event
	{
	public:
		Event(void* window) : m_Window(window), m_Handled(true) {}
		inline void* getWindow() { return this->m_Window; }
		virtual EventType getEventType() const = 0;
		virtual const char* toString() const = 0;
		bool m_Handled;
	private:
		void* m_Window;
	};

	class Dispatcher
	{
		template<typename T> using EventFn = std::function<bool(T&)>;
	public:
		Dispatcher(Event& event) : m_Event(event) {}

		template<typename T> bool dispatch(EventFn<T> function)
		{
			if (m_Event.getEventType() == T::getStaticType())
			{
				m_Event.m_Handled = function(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}
