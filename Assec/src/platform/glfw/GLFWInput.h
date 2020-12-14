#pragma once

#include "input/Joystick.h"

#include "GLFWWindowContext.h"

namespace assec::input
{
	class GLFWJoystick : public Joystick
	{
	public:
		GLFWJoystick(CONST_REF(int) id) : Joystick(graphics::joystickIDFromGLFWType(id)) {}
		~GLFWJoystick() = default;
		virtual std::vector<float> getJoystickAxes() const override;
		virtual std::vector<bool> getJoystickButtons() const override;
		virtual std::vector<bool> getJoystickHats() const override;
		virtual std::string getJoystickName() const override;
		virtual std::string getJoystickGUID() const override;
		virtual void* getJoystickUserPointer() const override;
		virtual void setJoystickUserPointer(void*) const override;
		virtual bool hasGamepadMapping() const override;
		virtual std::string getGamepadName() const override;
		virtual GamepadState getGamepadState() const override;
	private:
		INLINE int native() const { return graphics::toGLFWType(this->m_RendererID); }
	};
}