#pragma once
#include "Event.h"

namespace assec::events
{
	class PathDroppedEvent : public Event
	{
	public:
		PathDroppedEvent(void* window, int count, const char** paths) : Event::Event(window), m_Count(count), m_Paths(paths) {}
		~PathDroppedEvent() {}
		EVENT_CLASS_TYPE(EventType::PathDropped);
		int m_Count;
		const char** m_Paths;
	};
}