#pragma once

#include "Event.h"

namespace assec::events
{
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent(CONST_REF(float) delta) : Event::Event(nullptr), m_Delta(delta) { TIME_FUNCTION; }
		~AppUpdateEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(float) getDeltaTime() const { TIME_FUNCTION; return this->m_Delta; }
	private:
		float m_Delta;
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent(CONST_REF(float) delta) : Event::Event(nullptr), m_Delta(delta) { TIME_FUNCTION; }
		~AppRenderEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(float) getDeltaTime() const { TIME_FUNCTION; return this->m_Delta; }
	private:
		float m_Delta;
	};

	class PathDroppedEvent : public Event
	{
	public:
		PathDroppedEvent(const void* window, CONST_REF(std::vector<std::string>) paths) : Event::Event(window), m_Paths(paths) { TIME_FUNCTION; }
		~PathDroppedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(std::vector<std::string>) getPaths() const { TIME_FUNCTION; return this->m_Paths; }
	private:
		std::vector<std::string> m_Paths;
	};
} // namespace assec::events
