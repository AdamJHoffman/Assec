#pragma once

#include "Event.h"

namespace assec::events
{
	const class EventQueue
	{
	public:
		EventQueue() { TIME_FUNCTION; }
		~EventQueue() { TIME_FUNCTION; }
		void submit(ref<events::Event> event);
		void clear();
		inline std::vector<ref<events::Event>>& getEventQueue() { return this->m_Events; }
	private:
		std::vector<ref<events::Event>> m_Events = std::vector<ref<events::Event>>();
	};
} // assec::events
