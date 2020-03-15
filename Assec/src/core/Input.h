#pragma once
#include "event/Event.h"

namespace assec
{
	class InputManager
	{
	public:
		InputManager() : m_Keys(), m_MouseButtons() {}
		~InputManager() {}
		void onEvent(events::Event& event)
		{
			events::Dispatcher dispatcher = events::Dispatcher(event);
			dispatcher.dispatch<events::KeyPressedEvent>([this](events::KeyPressedEvent& event)
				{
					this->m_Keys[event.m_Keycode] = true;
					return false;
				});
			dispatcher.dispatch<events::KeyReleasedEvent>([this](events::KeyReleasedEvent& event)
				{
					this->m_Keys[event.m_Keycode] = false;
					return false;
				});
			dispatcher.dispatch<events::MouseButtonPressedEvent>([this](events::MouseButtonPressedEvent& event)
				{
					this->m_MouseButtons[event.m_Button] = true;
					return false;
				});
			dispatcher.dispatch<events::MouseButtonReleasedEvent>([this](events::MouseButtonReleasedEvent& event)
				{
					this->m_MouseButtons[event.m_Button] = false;
					return false;
				});
		}
		bool isKeyDown(const int keycode)
		{
			return this->m_Keys[keycode];
		}
		inline bool isMouseButtonDown(const int button) const
		{
			return this->m_MouseButtons[button];
		}
		bool m_Keys[255];
		bool m_MouseButtons[9];
	};
}