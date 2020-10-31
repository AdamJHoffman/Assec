#pragma once

#include "Event.h"

namespace assec::events
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(const void* window, const KEY& keycode, const int& scancode, const int& mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) { TIME_FUNCTION; }
		~KeyPressedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::KeyPressed);
		KEY m_Keycode;
		int m_Scancode, m_Mods;
	};

	class KeyRepeatedEvent : public Event
	{
	public:
		KeyRepeatedEvent(const void* window, const KEY& keycode, const int& scancode, const int& mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) { TIME_FUNCTION; }
		~KeyRepeatedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::KeyRepeated);
		KEY m_Keycode;
		int m_Scancode, m_Mods;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(const void* window, const KEY& keycode, const int& scancode) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode) {}
		~KeyReleasedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::KeyReleased);
		KEY m_Keycode;
		int m_Scancode;
	};

	class CharTypedEvent : public Event
	{
	public:
		CharTypedEvent(const void* window, const uint32_t& unicode) : Event::Event(window), m_Unicode(unicode) {}
		~CharTypedEvent() { TIME_FUNCTION; }
		EVENT_CLASS_TYPE(EventType::CharTyped);
		uint32_t m_Unicode;
	};
} // assec::events
