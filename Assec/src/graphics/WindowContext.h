#pragma once

#include "Window.h"
#include "Monitor.h"

namespace assec::graphics
{
	struct InitHints
	{
		bool joystickHatsAsButtons = true;
		AnglePlatformType anglePlatformType = AnglePlatformType::NONE;
		bool setCurrentDirectoyToResources = true;
		bool createBasicMenuBar = true;
	};

	class WindowContext
	{
	public:
		virtual ~WindowContext() = default;
		virtual void init(CONST_REF(InitHints) hints = InitHints()) = 0;
		virtual void terminate() = 0;
		virtual glm::vec3 getVersion() const = 0;
		virtual std::string getVersionAsString() const = 0;
		virtual std::pair<uint32_t, std::string> getError() const = 0;

		virtual const std::vector<scope<Monitor>> getMonitors() const = 0;
		virtual const scope<Monitor> getPrimaryMonitor() const = 0;

		virtual ref<Window> createWindow(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, 
			CONST_REF(std::string) title, const Monitor* monitor, const Window* share, 
			CONST_REF(EventCallBackFn) eventCallBack) const = 0;

		virtual void pollEvents() const = 0;
		virtual void waitEvents() const = 0;
		virtual void waitEventsTimeout(double) const = 0;
		virtual void postEmptyEvent() const = 0;

		virtual bool isRawMouseMotionSupported() const = 0;

		virtual std::string getKeyName(CONST_REF(KEY)) const = 0;
		virtual uint32_t getKeyScancode(CONST_REF(KEY)) const = 0;
		 
		//virtual cursor createCursor(cursorhints)
		//virtual cursor createStandardCursor(cursorhints)
		virtual void destroyCursor(CONST_REF(Cursor)) const = 0;
		 
		virtual bool isJoystickPresent(CONST_REF(JoystickID)) const = 0;
		virtual void updateGamepadMappings(CONST_REF(std::string)) const = 0;
		 
		virtual double getCurrentTime() const = 0;
		virtual void setCurrentTime(double) const = 0;
		virtual uint64_t getTimerValue() const = 0;
		virtual uint64_t getTimerFrequency() const = 0;
		 
		virtual CONST_REF(Window) getCurrentContext() const = 0;
		virtual bool isExtensionSupported(CONST_REF(std::string)) const = 0;
		
		INLINE CONST_REF(bool) initialized() const { TIME_FUNCTION; return this->m_Initialized; }
	protected:
		WindowContext() = default;

		bool m_Initialized = false;
	}; // namespace assec::graphics
}
