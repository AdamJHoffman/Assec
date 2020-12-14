#pragma once

#include "Event.h"

namespace assec::events
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(const void* window, CONST_REF(KEY) keycode, CONST_REF(int) scancode, CONST_REF(int) mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) { TIME_FUNCTION; }
		~KeyPressedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(KEY) getKeycode() const { TIME_FUNCTION; return this->m_Keycode; }
		INLINE CONST_REF(int) getScancde() const { TIME_FUNCTION; return this->m_Scancode; }
		INLINE CONST_REF(int) getMods() const { TIME_FUNCTION; return this->m_Mods; }
	private:
		KEY m_Keycode;
		int m_Scancode, m_Mods;
	};

	class KeyRepeatedEvent : public Event
	{
	public:
		KeyRepeatedEvent(const void* window, CONST_REF(KEY) keycode, CONST_REF(int) scancode, CONST_REF(int) mods) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode), m_Mods(mods) { TIME_FUNCTION; }
		~KeyRepeatedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(KEY) getKeycode() const { return this->m_Keycode; }
		INLINE CONST_REF(int) getScancde() const { return this->m_Scancode; }
		INLINE CONST_REF(int) getMods() const { return this->m_Mods; }
	private:
		KEY m_Keycode;
		int m_Scancode, m_Mods;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(const void* window, CONST_REF(KEY) keycode, CONST_REF(int) scancode) : Event::Event(window), m_Keycode(keycode), m_Scancode(scancode) {}
		~KeyReleasedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(KEY) getKeycode() const { return this->m_Keycode; }
		INLINE CONST_REF(int) getScancde() const { return this->m_Scancode; }
	private:
		KEY m_Keycode;
		int m_Scancode;
	};

	class CharTypedEvent : public Event
	{
	public:
		CharTypedEvent(const void* window, CONST_REF(uint32_t) unicode) : Event::Event(window), m_Unicode(unicode) {}
		~CharTypedEvent() { TIME_FUNCTION; }
		INLINE CONST_REF(uint32_t) getUnicode() const { return this->m_Unicode; }
	private:
		uint32_t m_Unicode;
	};
} // assec::events
