#pragma once
#include "Event.h"

namespace assec::events
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(void* window, int keycode, int scancode, int mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) {}
		~KeyPressedEvent() {}
		EVENT_CLASS_TYPE(EventType::KeyPressed);
		int m_Keycode, m_Scancode, m_Mods;
	};

	class KeyRepeatedEvent : public Event
	{
	public:
		KeyRepeatedEvent(void* window, int keycode, int scancode, int mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) {}
		~KeyRepeatedEvent() {}
		EVENT_CLASS_TYPE(EventType::KeyRepeated);
		int m_Keycode, m_Scancode, m_Mods;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(void* window, int keycode, int scancode) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode) {}
		~KeyReleasedEvent() {}
		EVENT_CLASS_TYPE(EventType::KeyReleased);
		int m_Keycode, m_Scancode;
	};

	class CharTypedEvent : public Event
	{
	public:
		CharTypedEvent(void* window, unsigned int unicode) : Event::Event(window), m_Unicode(unicode) {}
		~CharTypedEvent() {}
		EVENT_CLASS_TYPE(EventType::CharTyped);
		unsigned int m_Unicode;
	};
}
