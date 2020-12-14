#include "acpch.h"

#include "GLFWInput.h"

namespace assec::input
{
	std::vector<float> GLFWJoystick::getJoystickAxes() const
	{
		int count = 0;
		const float* values = glfwGetJoystickAxes(this->native(), &count);
		return std::vector<float>(values, values + count);
	}
	std::vector<bool> GLFWJoystick::getJoystickButtons() const
	{
		int count = 0;
		const bool* values = (const bool*)glfwGetJoystickButtons(this->native(), &count);
		return std::vector<bool>(values, values + count);
	}
	std::vector<bool> GLFWJoystick::getJoystickHats() const
	{
		int count = 0;
		const bool* values = (const bool*)glfwGetJoystickHats(this->native(), &count);
		return std::vector<bool>(values, values + count);
	}
	std::string GLFWJoystick::getJoystickName() const
	{
		return std::string(glfwGetJoystickName(this->native()));
	}
	std::string GLFWJoystick::getJoystickGUID() const
	{
		return std::string(glfwGetJoystickGUID(this->native()));
	}
	void* GLFWJoystick::getJoystickUserPointer() const
	{
		return glfwGetJoystickUserPointer(this->native());
	}
	void GLFWJoystick::setJoystickUserPointer(void* pointer) const
	{
		glfwSetJoystickUserPointer(this->native(), pointer);
	}
	bool GLFWJoystick::hasGamepadMapping() const
	{
		return glfwJoystickIsGamepad(this->native());
	}
	std::string GLFWJoystick::getGamepadName() const
	{
		return std::string(glfwGetGamepadName(this->native()));
	}
	GamepadState GLFWJoystick::getGamepadState() const
	{
		GLFWgamepadstate state;
		glfwGetGamepadState(this->native(), &state);
		GamepadState result = GamepadState();
		for (int i = 0; i < result.buttons.size(); ++i)
		{
			result.buttons[i] = state.buttons[i];
		}
		for (int i = 0; i < result.axes.size(); ++i)
		{
			result.axes[i] = state.axes[i];
		}
		return result;
	}
}