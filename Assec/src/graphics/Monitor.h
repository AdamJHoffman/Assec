#pragma once

#include <glm/glm.hpp>

namespace assec::graphics
{
	struct Videomode
	{
		const int width, height, redBits, greenBits, blueBits, refreshRate;
	};
	struct GammaRamp
	{
		unsigned short* red, * green, * blue;
		size_t size;
	};
	class Monitor
	{
	public:
		Monitor(const void* nativeMonitor) : m_NativeMonitor(nativeMonitor){TIME_FUNCTION;}
		~Monitor() { TIME_FUNCTION; }
		virtual glm::vec2 getPosition() const = 0;
		virtual glm::vec4 getWorkarea() const = 0;
		virtual glm::vec2 getPhysicalSize() const = 0;
		virtual glm::vec2 getContentScale() const = 0;
		virtual std::string getName() const = 0;
		virtual void* getUserPointer() const = 0;
		virtual void setUserPointer(void*) const = 0;
		virtual std::vector<Videomode> getSupportedVideoModes() const = 0;
		virtual Videomode getCurrentVideoMode() const = 0;
		virtual void setGamma(CONST_REF(float) gamma) const = 0;
		virtual GammaRamp getGammaRamp() const = 0;
		virtual void setGammaRamp(CONST_REF(GammaRamp)) const = 0;
		INLINE const void* getNativeMonitor() const { TIME_FUNCTION; return this->m_NativeMonitor; }
	protected:
		const void* m_NativeMonitor;
	};
} // namespace assec::graphics
