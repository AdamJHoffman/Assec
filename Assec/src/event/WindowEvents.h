#pragma once

#include <glm/glm.hpp>

#include "Event.h"

namespace assec::events
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowCloseEvent() { TIME_FUNCTION; }
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowFocusEvent() { TIME_FUNCTION; }
	};

	class WindowFocusLostEvent : public Event
	{
	public:
		WindowFocusLostEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowFocusLostEvent() { TIME_FUNCTION; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(const void* window, CONST_REF(glm::vec2) size) : Event::Event(window), m_Size(size) { TIME_FUNCTION; }
		~WindowResizeEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(glm::vec2) getSize() const { TIME_FUNCTION; return this->m_Size; }
	private:
		glm::vec2 m_Size = glm::vec2(0.0f);
	};

	class WindowContentScaleEvent : public Event
	{
	public:
		WindowContentScaleEvent(const void* window, CONST_REF(glm::vec2) scale) : Event::Event(window), m_Scale(scale) { TIME_FUNCTION; }
		~WindowContentScaleEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(glm::vec2) getScale() const { TIME_FUNCTION; return this->m_Scale; }
	private:
		glm::vec2 m_Scale = glm::vec2(0.0f);
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(const void* window, CONST_REF(glm::vec2) position) : Event::Event(window), m_Position(position) { TIME_FUNCTION; }
		~WindowMoveEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(glm::vec2) getPosition() const { TIME_FUNCTION; return this->m_Position; }
	private:
		glm::vec2 m_Position = glm::vec2(0.0f);
	};

	class WindowMinimizeEvent : public Event
	{
	public:
		WindowMinimizeEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowMinimizeEvent() { TIME_FUNCTION; }
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowMaximizeEvent() { TIME_FUNCTION; }
	};

	class WindowRestoreEvent : public Event
	{
	public:
		WindowRestoreEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowRestoreEvent() { TIME_FUNCTION; }
	};

	class WindowRefreshEvent : public Event
	{
	public:
		WindowRefreshEvent(const void* window) : Event::Event(window) { TIME_FUNCTION; }
		~WindowRefreshEvent() { TIME_FUNCTION; }
	};

} // assec::events
