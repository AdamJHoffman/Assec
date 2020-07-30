#pragma once
#include "Event.h"

namespace assec::events
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(void* window, int keycode, int scancode, int mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) { TIME_FUNCTION; }
		~KeyPressedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::KeyPressed);
		int m_Keycode, m_Scancode, m_Mods;
	};

	class KeyRepeatedEvent : public Event
	{
	public:
		KeyRepeatedEvent(void* window, int keycode, int scancode, int mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) { TIME_FUNCTION; }
		~KeyRepeatedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::KeyRepeated);
		int m_Keycode, m_Scancode, m_Mods;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(void* window, int keycode, int scancode) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode) {}
		~KeyReleasedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::KeyReleased);
		int m_Keycode, m_Scancode;
	};

	class CharTypedEvent : public Event
	{
	public:
		CharTypedEvent(void* window, uint32_t unicode) : Event::Event(window), m_Unicode(unicode) {}
		~CharTypedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::CharTyped);
		uint32_t m_Unicode;
	};
}
