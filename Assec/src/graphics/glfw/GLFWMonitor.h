#pragma once
#include "graphics/Monitor.h"
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	class GLFWVideomode : public Videomode
	{
	public:
		GLFWVideomode(const GLFWvidmode* videomode) : Videomode(videomode->width, videomode->height, videomode->redBits,
			videomode->greenBits, videomode->blueBits, videomode->refreshRate) {
			TIME_FUNCTION;
		}
		~GLFWVideomode() { TIME_FUNCTION; }
	};
	class GLFWMonitor : public Monitor
	{
	public:
		GLFWMonitor(GLFWmonitor* monitor);
		~GLFWMonitor() { TIME_FUNCTION; }

		virtual void setUserPointer(void* userPointer) const override;
		virtual void* getUserPointer() const override;
		virtual GammaRamp getGammaRamp() const override;
		virtual void setGammaRamp(const GammaRamp* gammaRamp) const override;
		virtual void setGamma(float gamma) const override;
	};
}
