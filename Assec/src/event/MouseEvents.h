#pragma once
#include "glm/glm.hpp"
#include "Event.h"

namespace assec::events
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const void* window, CONST_REF(glm::vec2) position) : Event::Event(window), m_Position(position) { TIME_FUNCTION; }
		~MouseMovedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(glm::vec2) getPosition() const { TIME_FUNCTION; return this->m_Position; }
	private:
		glm::vec2 m_Position;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(const void* window, CONST_REF(MOUSE) button, CONST_REF(int) mods) : Event::Event(window), m_Button(button), m_Mods(mods) { TIME_FUNCTION; }
		~MouseButtonPressedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(MOUSE) getMouseButton() const { TIME_FUNCTION; return this->m_Button; }
		INLINE CONST_REF(int) getMods() const { TIME_FUNCTION; return this->m_Mods; }
	private:
		MOUSE m_Button;
		int m_Mods;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(const void* window, CONST_REF(MOUSE) button) : Event::Event(window), m_Button(button) { TIME_FUNCTION; }
		~MouseButtonReleasedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(MOUSE) getMouseButton() const { TIME_FUNCTION; return this->m_Button; }
	private:
		MOUSE m_Button;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const void* window, CONST_REF(glm::vec2) offset) : Event::Event(window), m_Offset(offset) { TIME_FUNCTION; }
		~MouseScrolledEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(glm::vec2) getOffset() const { TIME_FUNCTION; return this->m_Offset; }
	private:
		glm::vec2 m_Offset;
	};

	class CursorEnteredEvent : public Event
	{
	public:
		CursorEnteredEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~CursorEnteredEvent() { TIME_FUNCTION; }
	};

	class CursorExitedEvent : public Event
	{
	public:
		CursorExitedEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~CursorExitedEvent() { TIME_FUNCTION; }
	};
} // assec::events
