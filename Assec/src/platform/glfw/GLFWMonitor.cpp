#include "acpch.h"

#include "GLFWMonitor.h"

namespace assec::graphics
{
	GLFWVideomode::GLFWVideomode(const void* videomode) : Videomode{ ((GLFWvidmode*)videomode)->width, ((GLFWvidmode*)videomode)->height, ((GLFWvidmode*)videomode)->redBits,
		((GLFWvidmode*)videomode)->greenBits, ((GLFWvidmode*)videomode)->blueBits, ((GLFWvidmode*)videomode)->refreshRate } {
		TIME_FUNCTION;
	}
	GLFWMonitor::GLFWMonitor(const void* monitor) : Monitor(monitor)
	{
		TIME_FUNCTION;
	}
	glm::vec2 GLFWMonitor::getPosition() const
	{
		TIME_FUNCTION;
		int x = 0, y = 0;
		glfwGetMonitorPos(this->native(), &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
	}
	glm::vec4 GLFWMonitor::getWorkarea() const
	{
		TIME_FUNCTION;
		int x = 0, y = 0, width = 0, height = 0;
		glfwGetMonitorWorkarea(this->native(), &x, &y, &width, &height);
		return glm::vec4{ static_cast<float>(x), static_cast<float>(y),
			static_cast<float>(width), static_cast<float>(height) };
	}
	glm::vec2 GLFWMonitor::getPhysicalSize() const 
	{
		TIME_FUNCTION;
		int width = 0, height = 0;
		glfwGetMonitorPhysicalSize(this->native(), &width, &height);
		return glm::vec2{ static_cast<float>(width), static_cast<float>(height) };
	}
	glm::vec2 GLFWMonitor::getContentScale() const 
	{
		TIME_FUNCTION;
		glm::vec2 result = glm::vec2(0.0f);
		glfwGetMonitorContentScale(this->native(), &result.x, &result.y);
		return result;
	}
	std::string GLFWMonitor::getName() const 
	{
		TIME_FUNCTION;
		return std::string(glfwGetMonitorName(this->native()));
	}
	void* GLFWMonitor::getUserPointer() const 
	{
		TIME_FUNCTION;
		return glfwGetMonitorUserPointer(this->native());
	}
	void GLFWMonitor::setUserPointer(void* pointer) const 
	{
		TIME_FUNCTION;
		return glfwSetMonitorUserPointer(this->native(), pointer);
	}
	std::vector<Videomode> GLFWMonitor::getSupportedVideoModes() const 
	{
		TIME_FUNCTION;
		std::vector<Videomode> result;
		int supportedVideoModes = 0;
		const GLFWvidmode* modes = glfwGetVideoModes(this->native(), &supportedVideoModes);
		for (int i = 0; i < supportedVideoModes; i++)
		{
			result.push_back(GLFWVideomode(&modes[i]));
		}
		return result;
	}
	Videomode GLFWMonitor::getCurrentVideoMode() const 
	{
		TIME_FUNCTION;
		return GLFWVideomode(glfwGetVideoMode(this->native()));
	}
	void GLFWMonitor::setGamma(CONST_REF(float) gamma) const
	{
		TIME_FUNCTION;
		glfwSetGamma(this->native(), gamma);
	}
	GammaRamp GLFWMonitor::getGammaRamp() const 
	{
		TIME_FUNCTION;
		const GLFWgammaramp* ramp = glfwGetGammaRamp(this->native());
		return GammaRamp{ ramp->red, ramp->green, ramp->blue, static_cast<size_t>(ramp->size) };
	}
	void GLFWMonitor::setGammaRamp(CONST_REF(GammaRamp) gammaRamp) const 
	{
		TIME_FUNCTION;
		GLFWgammaramp ramp;
		ramp.red = gammaRamp.red;
		ramp.green = gammaRamp.green;
		ramp.blue = gammaRamp.blue;
		ramp.size = static_cast<unsigned int>(gammaRamp.size);
		glfwSetGammaRamp(this->native(), &ramp);
	}
} // namespace assec::graphics
