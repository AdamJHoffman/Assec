#pragma once
#include "Event.h"

namespace assec::events
{
	const class EventQueue
	{
	public:
		EventQueue() { TIME_FUNCTION; }
		~EventQueue() { TIME_FUNCTION; }
		std::vector<ref<Event>> m_Events = std::vector<ref<Event>>();
	};
}
