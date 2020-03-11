#include "acpch.h"
#include "core/Core.h"
#include "OpenGLGraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	OpenGLGraphicsContext::OpenGLGraphicsContext() : GraphicsContext::GraphicsContext() {}
	OpenGLGraphicsContext::~OpenGLGraphicsContext() {}
	const void OpenGLGraphicsContext::init() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Assertion failed: {0}", "failed to initialize OpenGL");
		assec::Logger::CORE_LOGGER->getLogger()->info("successfully initlialized OpenGL: ");
		assec::Logger::CORE_LOGGER->getLogger()->info("	Vendor: {0}", glGetString(GL_VENDOR));
		assec::Logger::CORE_LOGGER->getLogger()->info("	Renderer: {0}", glGetString(GL_RENDERER));
		assec::Logger::CORE_LOGGER->getLogger()->info("	Version: {0}", glGetString(GL_VERSION));

	}
}