#include "acpch.h"
#include "GLFWMonitor.h"
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	GLFWVideomode::GLFWVideomode(const void* videomode) : Videomode(((GLFWvidmode*)videomode)->width, ((GLFWvidmode*)videomode)->height, ((GLFWvidmode*)videomode)->redBits,
		((GLFWvidmode*)videomode)->greenBits, ((GLFWvidmode*)videomode)->blueBits, ((GLFWvidmode*)videomode)->refreshRate) {
		TIME_FUNCTION;
	}
	GLFWMonitor::GLFWMonitor(void* monitor) : Monitor((void*)monitor, GLFWVideomode(glfwGetVideoMode((GLFWmonitor*)monitor)), std::vector<Videomode>(), 0, glm::vec<2, int>(0),
		glfwGetMonitorName((GLFWmonitor*)monitor), glm::vec<2, int>(0), glm::vec2(0), glm::vec<4, int>(0))
	{
		TIME_FUNCTION;
		const GLFWvidmode* modes = glfwGetVideoModes((GLFWmonitor*)monitor, &this->m_SupportedVideoModeCount);
		for (int i = 0; i < this->m_SupportedVideoModeCount; i++)
		{
			this->m_SupportedVideoModes.push_back(GLFWVideomode(&modes[i]));
		}
		glfwGetMonitorPhysicalSize((GLFWmonitor*)monitor, &this->m_PhysicalSize.x, &this->m_PhysicalSize.y);
		glfwGetMonitorContentScale((GLFWmonitor*)monitor, &this->m_ContentScale.x, &this->m_ContentScale.y);
		glfwGetMonitorPos((GLFWmonitor*)monitor, &this->m_VirtualPosition.x, &this->m_VirtualPosition.y);
		glfwGetMonitorWorkarea((GLFWmonitor*)monitor, &this->m_WorkArea.x, &this->m_WorkArea.x, &this->m_WorkArea.z, &this->m_WorkArea.w);
	}
	void GLFWMonitor::setUserPointer(void* userPointer) const
	{
		TIME_FUNCTION;
		glfwSetMonitorUserPointer((GLFWmonitor*)this->m_NativeMonitor, userPointer);
	}
	void* GLFWMonitor::getUserPointer() const
	{
		TIME_FUNCTION;
		return glfwGetMonitorUserPointer((GLFWmonitor*)this->m_NativeMonitor);
	}
	GammaRamp GLFWMonitor::getGammaRamp() const
	{
		TIME_FUNCTION;
		const GLFWgammaramp* ramp = glfwGetGammaRamp((GLFWmonitor*)this->m_NativeMonitor);
		return GammaRamp(ramp->red, ramp->green, ramp->blue, ramp->size);
	}
	void GLFWMonitor::setGammaRamp(const GammaRamp* gammaRamp) const
	{
		TIME_FUNCTION;
		GLFWgammaramp ramp;
		ramp.red = gammaRamp->m_Red;
		ramp.green = gammaRamp->m_Green;
		ramp.blue = gammaRamp->m_Blue;
		ramp.size = static_cast<unsigned int>(gammaRamp->m_Size);
		glfwSetGammaRamp((GLFWmonitor*)this->m_NativeMonitor, &ramp);
	}
	void GLFWMonitor::setGamma(float gamma) const
	{
		TIME_FUNCTION;
		glfwSetGamma((GLFWmonitor*)this->m_NativeMonitor, gamma);
	}
}
