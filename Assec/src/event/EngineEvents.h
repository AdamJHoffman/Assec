#pragma once
#include "Event.h"

namespace assec::events
{
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent(void* window, float delta) : Event::Event(window), m_Delta(delta) {}
		~AppTickEvent() {}
		EVENT_CLASS_TYPE(EventType::AppTick);
		float m_Delta;
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent(void* window, float delta) : Event::Event(window), m_Delta(delta) {}
		~AppUpdateEvent() {}
		EVENT_CLASS_TYPE(EventType::AppUpdate);
		float m_Delta;
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent(void* window, float delta) : Event::Event(window), m_Delta(delta) {}
		~AppRenderEvent() {}
		EVENT_CLASS_TYPE(EventType::AppRender);
		float m_Delta;
	};

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
