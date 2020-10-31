#pragma once

#include "graphics/Monitor.h"

namespace assec::graphics
{
	class GLFWVideomode : public Videomode
	{
	public:
		GLFWVideomode(const void* videomode);
		~GLFWVideomode() { TIME_FUNCTION; }
	};
	class GLFWMonitor : public Monitor
	{
	public:
		GLFWMonitor(const void* monitor);
		~GLFWMonitor() { TIME_FUNCTION; }

		virtual void setUserPointer(void* userPointer) const override;
		virtual void* getUserPointer() const override;
		virtual GammaRamp getGammaRamp() const override;
		virtual void setGammaRamp(const GammaRamp& gammaRamp) const override;
		virtual void setGamma(const float& gamma) const override;
	};
} // assec::graphics
