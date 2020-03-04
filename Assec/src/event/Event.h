#pragma once

#include "acpch.h"
#include "graphics/Window.h"

namespace assec
{

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

#define EVENT_CLASS_TYPE(type) virtual const char* toString() const override { return #type; }

	class Event
	{
	public:
		Event(Window& window, EventType& type) : m_Window(window), m_type(type), m_Handled(true) {}
		inline Window& getWindow() { return this->m_Window; }
		inline EventType& getEventType() { return this->m_type; }
		virtual const char* toString() const = 0;
		bool m_Handled;
	private:
		Window& m_Window;
		EventType& m_type;
	};

	class Dispatcher
	{
		template<typename T> using EventFn = std::function<bool(T&)>;
	public:
		Dispatcher(Event& event) : m_Event(event) {}
		~Dispatcher() {}
		template<typename T> bool dispatch(EventFn<T> function)
		{
			if (this->m_Event.getEventType() == T.getEventType())
			{
				this->m_Event.m_Handled = func(*(T*)&m_Event);
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}
