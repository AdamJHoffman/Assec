#pragma once
#include "glm/glm.hpp"
#include "Event.h"

namespace assec::events
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const void* window, const glm::vec2& position) : Event::Event(window), m_Position(position) { TIME_FUNCTION; }
		~MouseMovedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::MouseMoved);
		glm::vec2 m_Position;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(const void* window, const MOUSE& button, const int& mods) : Event::Event(window), m_Button(button), m_Mods(mods) { TIME_FUNCTION; }
		~MouseButtonPressedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::MouseButtonPressed);
		MOUSE m_Button;
		int m_Mods;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(const void* window, const MOUSE& button) : Event::Event(window), m_Button(button) { TIME_FUNCTION; }
		~MouseButtonReleasedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::MouseButtonReleased);
		MOUSE m_Button;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const void* window, const glm::vec2& offset) : Event::Event(window), m_Offset(offset) { TIME_FUNCTION; }
		~MouseScrolledEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::MouseScrolled);
		glm::vec2 m_Offset;
	};

	class CursorEnteredEvent : public Event
	{
	public:
		CursorEnteredEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~CursorEnteredEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::CursorEntered);
	};

	class CursorExitedEvent : public Event
	{
	public:
		CursorExitedEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~CursorExitedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::CursorExited);
	};
} // assec::events
