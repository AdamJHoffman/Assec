#pragma once

#include "Event.h"

namespace assec::events
{
	const class EventQueue
	{
	public:
		EventQueue() { TIME_FUNCTION; }
		~EventQueue() { TIME_FUNCTION; }
		void submit(Event* event);
		void clear();
		inline std::vector<Event*>& getEventQueue() { return this->m_Events; }
	private:
		std::vector<Event*> m_Events = std::vector<Event*>();
	};
} // assec::events
