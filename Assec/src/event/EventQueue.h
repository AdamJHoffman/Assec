#pragma once
#include "Event.h"

namespace assec::events
{
	const class EventQueue
	{
	public:
		EventQueue() { TIME_FUNCTION; }
		~EventQueue() { TIME_FUNCTION; }
		const void submit(Event* event)
		{
			this->m_Events.push_back(event);
		}
		const void clear()
		{
			for (auto event : this->m_Events)
			{
				delete event;
			}
			this->m_Events.clear();
		}
		inline const std::vector<Event*>& getEventQueue() const
		{
			return this->m_Events;
		}
	private:
		std::vector<Event*> m_Events = std::vector<Event*>();
	};
}
