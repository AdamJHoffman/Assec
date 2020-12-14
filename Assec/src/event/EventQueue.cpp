#include "acpch.h"

#include "EventQueue.h"

namespace assec::events
{
	void EventQueue::submit(ref<events::Event> event)
	{
		TIME_FUNCTION;
		this->m_Events.push_back(event);
	}
	void EventQueue::clear()
	{
		TIME_FUNCTION;
		this->m_Events.clear();
	}
} // namespace assec::events
