#pragma once
#include "acpch.h"

#include <glm/glm.hpp>

namespace assec::graphics
{
	class Videomode
	{
	public:
		struct VideomodeProps
		{
			int m_Width, m_Height, m_RedBits, m_GreenBits, m_BlueBits, m_RefreshRate;
		};
		Videomode(const VideomodeProps& props)
			: m_Width(props.m_Width), m_Height(props.m_Height), m_RedBits(props.m_RedBits), m_GreenBits(props.m_GreenBits), m_BlueBits(props.m_BlueBits), m_RefreshRate(props.m_RefreshRate)
		{
			TIME_FUNCTION;
		}
		~Videomode() { TIME_FUNCTION; }
		const int m_Width, m_Height, m_RedBits, m_GreenBits, m_BlueBits, m_RefreshRate;
	};
	class GammaRamp
	{
	public:
		GammaRamp(unsigned short* red, unsigned short* green, unsigned short* blue, size_t size)
			: m_Red(red), m_Green(green), m_Blue(blue), m_Size(size)
		{
			TIME_FUNCTION;
		}
		~GammaRamp() { TIME_FUNCTION; }
		unsigned short* m_Red, * m_Green, * m_Blue;
		size_t m_Size;
	};
	class Monitor
	{
	public:
		struct MonitorProps
		{
			void* m_NativeMonitor;
			Videomode m_CrrentVideoMode;
			std::vector<Videomode> m_SupportedVideoModes;
			glm::vec<2, int> m_VirtualPosition, m_PhysicalSize;
			std::string m_Name;
			glm::vec2& m_ContentScale;
			glm::vec<4, int> m_WorkArea;
		};
		Monitor(const MonitorProps& props)
			: m_NativeMonitor(props.m_NativeMonitor), m_CurrentVideoMode(props.m_CrrentVideoMode), m_SupportedVideoModes(props.m_SupportedVideoModes),
			m_VirtualPosition(props.m_VirtualPosition), m_Name(props.m_Name), m_PhysicalSize(props.m_PhysicalSize), m_ContentScale(props.m_ContentScale), m_WorkArea(props.m_WorkArea)
		{
			TIME_FUNCTION;
		}
		~Monitor() { TIME_FUNCTION; }
		const void* m_NativeMonitor;
		Videomode m_CurrentVideoMode;
		std::vector<Videomode> m_SupportedVideoModes;
		glm::vec<2, int> m_VirtualPosition;
		std::string m_Name;
		glm::vec<2, int> m_PhysicalSize;
		glm::vec2 m_ContentScale;
		glm::vec<4, int> m_WorkArea;

		virtual void setUserPointer(void* userPointer) const = 0;
		virtual void* getUserPointer() const = 0;
		virtual GammaRamp getGammaRamp() const = 0;
		virtual void setGammaRamp(const GammaRamp& gammaRamp) const = 0;
		virtual void setGamma(const float& gamma) const = 0;
	};
}
