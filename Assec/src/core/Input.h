#pragma once
#include "event/Event.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"



namespace assec
{
	class Input
	{
	public:
		static void onEvent(const events::Event& event)
		{
			TIME_FUNCTION;
			events::Dispatcher dispatcher = events::Dispatcher(event);
			dispatcher.dispatch<events::KeyPressedEvent>([&](events::KeyPressedEvent& event)
				{
					TIME_FUNCTION;
					m_Keys[event.m_Keycode] = true;
					return false;
				});
			dispatcher.dispatch<events::KeyReleasedEvent>([&](events::KeyReleasedEvent& event)
				{
					TIME_FUNCTION;
					m_Keys[event.m_Keycode] = false;
					return false;
				});
			dispatcher.dispatch<events::MouseButtonPressedEvent>([&](events::MouseButtonPressedEvent& event)
				{
					TIME_FUNCTION;
					m_MouseButtons[event.m_Button] = true;
					return false;
				});
			dispatcher.dispatch<events::MouseButtonReleasedEvent>([&](events::MouseButtonReleasedEvent& event)
				{
					TIME_FUNCTION;
					m_MouseButtons[event.m_Button] = false;
					return false;
				});
		}
		static bool isKeyDown(const int keycode)
		{
			TIME_FUNCTION;
			return m_Keys[keycode];
		}
		static bool isMouseButtonDown(const int button)
		{
			TIME_FUNCTION;
			return m_MouseButtons[button];
		}
		static bool m_Keys[500];
		static bool m_MouseButtons[9];
	private:
		Input() {}
		~Input() {}
	};
}
