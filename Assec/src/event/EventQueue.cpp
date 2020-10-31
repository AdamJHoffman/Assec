#include "acpch.h"

#include "EventQueue.h"

namespace assec::events
{
	void EventQueue::submit(Event* event)
	{
		this->m_Events.push_back(event);
	}
	void EventQueue::clear()
	{
		for (auto event : this->m_Events)
		{
			delete event;
		}
		this->m_Events.clear();
	}
} // assec::events
