#pragma once

#include <array>
#include <string>
#include <vector>

#include <core/KeyCode.h>

namespace assec::input
{
	struct GamepadState
	{
		std::array<bool, 15> buttons;
		std::array<float, 6> axes;

		CONST_REF(bool) getAButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_A)];
		}
		CONST_REF(bool) getBButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_B)];
		}
		CONST_REF(bool) getXButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_X)];
		}
		CONST_REF(bool) getYButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_Y)];
		}
		CONST_REF(bool) getLeftBumperButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_LEFT_BUMPER)];
		}
		CONST_REF(bool) getRightBumperButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_RIGHT_BUMPER)];
		}
		CONST_REF(bool) getBackButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_BACK)];
		}
		CONST_REF(bool) getStartButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_START)];
		}
		CONST_REF(bool) getGuideButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_GUIDE)];
		}
		CONST_REF(bool) getLeftThumbButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_LEFT_THUMB)];
		}
		CONST_REF(bool) getRightThumbButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_RIGHT_THUMB)];
		}
		CONST_REF(bool) getDPadUpButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_DPAD_UP)];
		}
		CONST_REF(bool) getDPadRightButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_DPAD_RIGHT)];
		}
		CONST_REF(bool) getDPadDownButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_DPAD_DOWN)];
		}
		CONST_REF(bool) getDPadLeftButton() const
		{
			return this->buttons[std::underlying_type_t<GamepadButton>(GamepadButton::BUTTON_DPAD_LEFT)];
		}

		CONST_REF(float) getLeftXAxis() const
		{
			return this->axes[std::underlying_type_t<GamepadButton>(GamepadAxis::AXIS_LEFT_X)];
		}
		CONST_REF(float) getLeftYAxis() const
		{
			return this->axes[std::underlying_type_t<GamepadButton>(GamepadAxis::AXIS_LEFT_Y)];
		}
		CONST_REF(float) getRightXAxis() const
		{
			return this->axes[std::underlying_type_t<GamepadButton>(GamepadAxis::AXIS_RIGHT_X)];
		}
		CONST_REF(float) getRightYAxis() const
		{
			return this->axes[std::underlying_type_t<GamepadButton>(GamepadAxis::AXIS_RIGHT_Y)];
		}
		CONST_REF(float) getLeftTrigger() const
		{
			return this->axes[std::underlying_type_t<GamepadButton>(GamepadAxis::AXIS_LEFT_TRIGGER)];
		}
		CONST_REF(float) getRightTrigger() const
		{
			return this->axes[std::underlying_type_t<GamepadButton>(GamepadAxis::AXIS_RIGHT_TRIGGER)];
		}
	};

	class Joystick
	{
	public:
		virtual ~Joystick() = default;
		virtual std::vector<float> getJoystickAxes() const = 0;
		virtual std::vector<bool> getJoystickButtons() const = 0;
		virtual std::vector<bool> getJoystickHats() const = 0;
		virtual std::string getJoystickName() const = 0;
		virtual std::string getJoystickGUID() const = 0;
		virtual void* getJoystickUserPointer() const = 0;
		virtual void setJoystickUserPointer(void*) const = 0;
		virtual bool hasGamepadMapping() const = 0;
		virtual std::string getGamepadName() const = 0;
		virtual GamepadState getGamepadState() const = 0;

		INLINE CONST_REF(JoystickID) getJoystickID() const { TIME_FUNCTION; return this->m_RendererID; }
	protected:
		Joystick(JoystickID rendererID) : m_RendererID(rendererID) {}

		JoystickID m_RendererID;
	};
}