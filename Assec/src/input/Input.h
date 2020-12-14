#pragma once

#include "event/Event.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"

#include "input/Joystick.h"

namespace assec::input
{
	class Input
	{
	public:
		static void onEvent(const events::Event& event);
		static bool isKeyDown(const KEY& keycode);
		static bool isMouseButtonDown(const MOUSE& button);
		static CONST_REF(std::vector<ref<Joystick>>) getConnectedJoysticks();

		static void onJoyStickConnected(ref<Joystick> id);
		static void onJoyStickDisconnected(JoystickID id);

	private:
		Input() {}
		~Input() {}

		static std::array<bool, 200> s_Keys;
		static std::array<bool, 15> s_MouseButtons;
		static std::vector<ref<Joystick>> s_Joysticks;
	};
} // namespace assec
