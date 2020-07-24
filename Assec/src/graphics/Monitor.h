#pragma once
#include "acpch.h"

namespace assec::graphics
{
	class Videomode
	{
	public:
		Videomode(const int& width, const int& height, const int& redBits, const int& greenBits, const int& blueBits, const int& refreshRate)
			: m_Width(width), m_Height(height), m_RedBits(redBits), m_GreenBits(greenBits), m_BlueBits(blueBits), m_RefreshRate(refreshRate)
		{
			TIME_FUNCTION;
		}
		~Videomode() { TIME_FUNCTION; }
		const int& m_Width;
		const int& m_Height;
		const int& m_RedBits;
		const int& m_GreenBits;
		const int& m_BlueBits;
		const int& m_RefreshRate;
	};
	class GammaRamp
	{
	public:
		GammaRamp(unsigned short* red, unsigned short* green, unsigned short* blue, unsigned int size)
			: m_Red(red), m_Green(green), m_Blue(blue), m_Size(size)
		{
			TIME_FUNCTION;
		}
		~GammaRamp() { TIME_FUNCTION; }
		unsigned short* m_Red;
		unsigned short* m_Green;
		unsigned short* m_Blue;
		unsigned int m_Size;
	};
	class Monitor
	{
	public:
		Monitor(void* nativeMonitor, Videomode& currentVideoMode, std::vector<Videomode> supportedVideoModes, int supportedVideoModesCount,
			glm::vec<2, int>& virtualPosition, const char* name, glm::vec<2, int>& physicalSize, glm::vec2& contentScale, glm::vec<4, int>& workArea)
			: m_NativeMonitor(nativeMonitor), m_CurrentVideoMode(currentVideoMode), m_SupportedVideoModes(supportedVideoModes), m_SupportedVideoModeCount(supportedVideoModesCount),
			m_VirtualPosition(virtualPosition), m_Name(name), m_PhysicalSize(physicalSize), m_ContentScale(contentScale), m_WorkArea(workArea)
		{
			TIME_FUNCTION;
		}
		~Monitor() { TIME_FUNCTION; }
		void* m_NativeMonitor;
		Videomode& m_CurrentVideoMode;
		std::vector<Videomode> m_SupportedVideoModes;
		int& m_SupportedVideoModeCount;
		glm::vec<2, int>& m_VirtualPosition;
		const char* m_Name;
		glm::vec<2, int>& m_PhysicalSize;
		glm::vec2& m_ContentScale;
		glm::vec<4, int>& m_WorkArea;

		virtual void setUserPointer(void* userPointer) const = 0;
		virtual void* getUserPointer() const = 0;
		virtual GammaRamp getGammaRamp() const = 0;
		virtual void setGammaRamp(const GammaRamp* gammaRamp) const = 0;
		virtual void setGamma(float gamma) const = 0;
	};
}
