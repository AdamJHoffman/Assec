#pragma once
#include "Event.h"

namespace assec::events
{
	const class EventQueue
	{
	public:
		EventQueue() {}
		~EventQueue() {}
		std::vector<ref<Event>> m_Events = std::vector<ref<Event>>();
	};
}