#pragma once
#include "glm/glm.hpp"
#include "Event.h"

namespace assec::events
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(void* window, glm::vec2 position) : Event::Event(window), m_Position(position) {}
		~MouseMovedEvent() {}
		EVENT_CLASS_TYPE(EventType::MouseMoved);
		glm::vec2 m_Position;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(void* window, int button, int mods) : Event::Event(window), m_Button(button), m_Mods(mods) {}
		~MouseButtonPressedEvent() {}
		EVENT_CLASS_TYPE(EventType::MouseButtonPressed);
		int m_Button, m_Mods;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(void* window, int button) : Event::Event(window), m_Button(button) {}
		~MouseButtonReleasedEvent() {}
		EVENT_CLASS_TYPE(EventType::MouseButtonReleased);
		int m_Button;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(void* window, glm::vec2 offset) : Event::Event(window), m_Offset(offset) {}
		~MouseScrolledEvent() {}
		EVENT_CLASS_TYPE(EventType::MouseScrolled);
		glm::vec2 m_Offset;
	};

	class CursorEnteredEvent : public Event
	{
	public:
		CursorEnteredEvent(void* window) : Event::Event(window) {}
		~CursorEnteredEvent() {}
		EVENT_CLASS_TYPE(EventType::CursorEntered);
	};

	class CursorExitedEvent : public Event
	{
	public:
		CursorExitedEvent(void* window) : Event::Event(window) {}
		~CursorExitedEvent() {}
		EVENT_CLASS_TYPE(EventType::CursorExited);
	};
}