#include "acpch.h"

#include "Input.h"

namespace assec
{
	void Input::onEvent(const events::Event& event)
	{
		TIME_FUNCTION;
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::KeyPressedEvent>([&](const events::KeyPressedEvent& event)
			{
				TIME_FUNCTION;
				m_Keys[static_cast<std::underlying_type_t<KEY>>(event.m_Keycode)] = true;
				return false;
			});
		dispatcher.dispatch<events::KeyReleasedEvent>([&](const events::KeyReleasedEvent& event)
			{
				TIME_FUNCTION;
				m_Keys[static_cast<std::underlying_type_t<KEY>>(event.m_Keycode)] = false;
				return false;
			});
		dispatcher.dispatch<events::MouseButtonPressedEvent>([&](const events::MouseButtonPressedEvent& event)
			{
				TIME_FUNCTION;
				m_MouseButtons[static_cast<std::underlying_type_t<MOUSE>>(event.m_Button)] = true;
				return false;
			});
		dispatcher.dispatch<events::MouseButtonReleasedEvent>([&](const events::MouseButtonReleasedEvent& event)
			{
				TIME_FUNCTION;
				m_MouseButtons[static_cast<std::underlying_type_t<MOUSE>>(event.m_Button)] = false;
				return false;
			});
	}
	bool Input::isKeyDown(const KEY& keycode)
	{
		TIME_FUNCTION;
		return m_Keys[static_cast<std::underlying_type_t<KEY>>(keycode)];
	}
	bool Input::isMouseButtonDown(const KEY& button)
	{
		TIME_FUNCTION;
		return m_MouseButtons[static_cast<std::underlying_type_t<KEY>>(button)];
	}
	bool Input::m_Keys[500] = { 0 };
	bool Input::m_MouseButtons[9] = { 0 };
}
