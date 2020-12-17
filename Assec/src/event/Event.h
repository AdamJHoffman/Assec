#pragma once

#include "acpch.h"

#include "core/KeyCode.h"

#include "util/Profiler.h"

namespace assec::events
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowFocus, WindowLostFocus, WindowResize, WindowContentScale, WindowMove, WindowMinimize, WindowMaximize, WindowRestore, WindowRefresh,
		AppUpdate, AppRender, PathDropped,
		KeyPressed, KeyReleased, KeyRepeated, CharTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, CursorEntered, CursorExited
	};

	class Event
	{
	public:
		Event(const void* window) : m_Window(window), handled(false) { TIME_FUNCTION; }
		virtual ~Event() { TIME_FUNCTION; }
		inline const void* getWindow() { TIME_FUNCTION; return this->m_Window; }
		CONST_REF(std::string) toString() const { TIME_FUNCTION; return typeid(this).name(); }
		bool handled;
	private:
		const void* m_Window;
	};

	class MouseEvent : public Event
	{
	public:
		MouseEvent(const void* window) : Event::Event(window) {}
		virtual ~MouseEvent() { TIME_FUNCTION; }
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent(const void* window) : Event::Event(window) {}
		virtual ~KeyEvent() { TIME_FUNCTION; }
	};
	
} // namespace assec::events
