#pragma once

#include "graphics/Monitor.h"

#include "GLFWWindowContext.h"

namespace assec::graphics
{
	struct GLFWVideomode : public Videomode
	{
		GLFWVideomode(const void* videomode);
	};
	class GLFWMonitor : public Monitor
	{
	public:
		GLFWMonitor(const void* monitor);
		~GLFWMonitor() { TIME_FUNCTION; }

		virtual glm::vec2 getPosition() const override;
		virtual glm::vec4 getWorkarea() const override;
		virtual glm::vec2 getPhysicalSize() const override;
		virtual glm::vec2 getContentScale() const override;
		virtual std::string getName() const override;
		virtual void* getUserPointer() const override;
		virtual void setUserPointer(void*) const override;
		virtual std::vector<Videomode> getSupportedVideoModes() const override;
		virtual Videomode getCurrentVideoMode() const override;
		virtual void setGamma(CONST_REF(float)) const override;
		virtual GammaRamp getGammaRamp() const override;
		virtual void setGammaRamp(CONST_REF(GammaRamp)) const override;
	private:
		INLINE GLFWmonitor* native() const { return (GLFWmonitor*)this->m_NativeMonitor; }
	};
} // assec::graphics
