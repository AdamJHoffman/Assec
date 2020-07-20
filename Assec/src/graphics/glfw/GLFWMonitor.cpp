#include "acpch.h"
#include "GLFWMonitor.h"

namespace assec::graphics
{
	GLFWMonitor::GLFWMonitor(GLFWmonitor* monitor) : Monitor((void*)monitor, GLFWVideomode(glfwGetVideoMode(monitor)), std::vector<Videomode>(), 0, glm::vec<2, int>(0),
		glfwGetMonitorName(monitor), glm::vec<2, int>(0), glm::vec2(0), glm::vec<4, int>(0))
	{
		const GLFWvidmode* modes = glfwGetVideoModes(monitor, &this->m_SupportedVideoModeCount);
		for (int i = 0; i < this->m_SupportedVideoModeCount; i++)
		{
			this->m_SupportedVideoModes.push_back(GLFWVideomode(&modes[i]));
		}
		glfwGetMonitorPhysicalSize(monitor, &this->m_PhysicalSize.x, &this->m_PhysicalSize.y);
		glfwGetMonitorContentScale(monitor, &this->m_ContentScale.x, &this->m_ContentScale.y);
		glfwGetMonitorPos(monitor, &this->m_VirtualPosition.x, &this->m_VirtualPosition.y);
		glfwGetMonitorWorkarea(monitor, &this->m_WorkArea.x, &this->m_WorkArea.x, &this->m_WorkArea.z, &this->m_WorkArea.w);
	}
	void GLFWMonitor::setUserPointer(void* userPointer) const
	{
		glfwSetMonitorUserPointer((GLFWmonitor*)this->m_NativeMonitor, userPointer);
	}
	void* GLFWMonitor::getUserPointer() const
	{
		return glfwGetMonitorUserPointer((GLFWmonitor*)this->m_NativeMonitor);
	}
	GammaRamp GLFWMonitor::getGammaRamp() const
	{
		const GLFWgammaramp* ramp = glfwGetGammaRamp((GLFWmonitor*)this->m_NativeMonitor);
		return GammaRamp(ramp->red, ramp->green, ramp->blue, ramp->size);
	}
	void GLFWMonitor::setGammaRamp(const GammaRamp* gammaRamp) const
	{
		GLFWgammaramp ramp;
		ramp.red = gammaRamp->m_Red;
		ramp.green = gammaRamp->m_Green;
		ramp.blue = gammaRamp->m_Blue;
		ramp.size = gammaRamp->m_Size;
		glfwSetGammaRamp((GLFWmonitor*)this->m_NativeMonitor, &ramp);
	}
	void GLFWMonitor::setGamma(float gamma) const
	{
		glfwSetGamma((GLFWmonitor*)this->m_NativeMonitor, gamma);
	}
}
