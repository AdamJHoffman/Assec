#pragma once
#include "graphics/WindowContext.h"

#include "GLFWMonitor.h"

namespace assec::graphics
{
	class GLFWWindowContext : public WindowContext
	{
	public:
		GLFWWindowContext();
		~GLFWWindowContext();
		virtual void init(CONST_REF(InitHints) hints) override;
		virtual void terminate() override;
		virtual glm::vec3 getVersion() const override;
		virtual std::string getVersionAsString() const override;
		virtual std::pair<uint32_t, std::string> getError() const override;

		virtual const std::vector<scope<Monitor>> getMonitors() const override;
		virtual const scope<Monitor> getPrimaryMonitor() const override;

		virtual ref<Window> createWindow(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height,
			CONST_REF(std::string) title, const Monitor* monitor, const Window* share,
			CONST_REF(EventCallBackFn) eventCallBack) const override;

		virtual void pollEvents() const override;
		virtual void waitEvents() const override;
		virtual void waitEventsTimeout(double) const override;
		virtual void postEmptyEvent() const override;

		virtual bool isRawMouseMotionSupported() const override;

		virtual std::string getKeyName(CONST_REF(KEY) key) const override;
		virtual uint32_t getKeyScancode(CONST_REF(KEY) key) const override;

		//virtual cursor createCursor(cursorhints)
		//virtual cursor createStandardCursor(cursorhints)
		virtual void destroyCursor(CONST_REF(Cursor)) const override;

		virtual bool isJoystickPresent(CONST_REF(JoystickID)) const override;
		virtual void updateGamepadMappings(CONST_REF(std::string)) const override;

		virtual double getCurrentTime() const override;
		virtual void setCurrentTime(double time) const override;
		virtual uint64_t getTimerValue() const override;
		virtual uint64_t getTimerFrequency() const override;

		virtual CONST_REF(Window) getCurrentContext() const override;
		virtual CONST_REF(bool) isExtensionSupported(CONST_REF(std::string)) const override;
	};

	const uint32_t toGLFWType(CONST_REF(KEY) key);
	const uint32_t toGLFWType(CONST_REF(MOUSE) button);
	const uint32_t toGLFWType(CONST_REF(AnglePlatformType) anglePlatformType);
	const uint32_t toGLFWType(CONST_REF(WindowAttribute) anglePlatformType);
	const uint32_t toGLFWType(CONST_REF(CursorMode) mode);
	const uint32_t toGLFWType(CONST_REF(JoystickID) id);

	const KEY keyFromGLFWType(CONST_REF(int) key);
	const MOUSE buttonFromGLFWType(CONST_REF(int) button);
	const CursorMode cursorModeFromGLFWType(CONST_REF(int) mode);
	const JoystickID joystickIDFromGLFWType(CONST_REF(int) id);

} // namespace assec::graphics
