#include "acpch.h"

#include "Input.h"

#include "util/Dispatcher.h"

namespace assec::input
{
	void Input::onEvent(const events::Event& event)
	{
		TIME_FUNCTION;
		util::Dispatcher dispatcher = util::Dispatcher(event);
		dispatcher.dispatch<events::KeyPressedEvent>([&](const events::KeyPressedEvent& event)
			{
				s_Keys[static_cast<std::underlying_type_t<KEY>>(event.getKeycode())] = true;
				return false;
			});
		dispatcher.dispatch<events::KeyReleasedEvent>([&](const events::KeyReleasedEvent& event)
			{
				s_Keys[static_cast<std::underlying_type_t<KEY>>(event.getKeycode())] = false;
				return false;
			});
		dispatcher.dispatch<events::MouseButtonPressedEvent>([&](const events::MouseButtonPressedEvent& event)
			{
				s_MouseButtons[static_cast<std::underlying_type_t<MOUSE>>(event.getMouseButton())] = true;
				return false;
			});
		dispatcher.dispatch<events::MouseButtonReleasedEvent>([&](const events::MouseButtonReleasedEvent& event)
			{
				s_MouseButtons[static_cast<std::underlying_type_t<MOUSE>>(event.getMouseButton())] = false;
				return false;
			});
	}
	bool Input::isKeyDown(const KEY& keycode)
	{
		TIME_FUNCTION;
		return s_Keys[static_cast<std::underlying_type_t<KEY>>(keycode)];
	}
	bool Input::isMouseButtonDown(const MOUSE& button)
	{
		TIME_FUNCTION;
		return s_MouseButtons[static_cast<std::underlying_type_t<MOUSE>>(button)];
	}
	CONST_REF(std::vector<ref<Joystick>>) Input::getConnectedJoysticks()
	{
		return s_Joysticks;
	}
	void Input::onJoyStickConnected(ref<Joystick> joystick)
	{
		s_Joysticks.push_back(joystick);
	}
	void Input::onJoyStickDisconnected(JoystickID id)
	{
		s_Joysticks.erase(std::remove_if(s_Joysticks.begin(), s_Joysticks.end(), [&id](CONST_REF(ref<Joystick>) joystick)
			{
				return joystick->getJoystickID() == id;
			}), s_Joysticks.end());
	}


	std::array<bool, 200> Input::s_Keys = { 0 };
	std::array<bool, 15> Input::s_MouseButtons = { 0 };
	std::vector<ref<Joystick>> Input::s_Joysticks;
} // namespace assec
