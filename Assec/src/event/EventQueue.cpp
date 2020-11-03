#include "acpch.h"

#include "EventQueue.h"

namespace assec::events
{
	void EventQueue::submit(ref<events::Event> event)
	{
		this->m_Events.push_back(event);
	}
	void EventQueue::clear()
	{
		this->m_Events.clear();
	}
} // assec::events
