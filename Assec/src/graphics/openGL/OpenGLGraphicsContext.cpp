#include "acpch.h"
#include "OpenGLGraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	OpenGLGraphicsContext::OpenGLGraphicsContext() : GraphicsContext::GraphicsContext() {}
	OpenGLGraphicsContext::~OpenGLGraphicsContext() {}
	const void OpenGLGraphicsContext::init() const
	{
		const char* validate = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ? "successfully initlialized OpenGL: " : "failed to initialize OpenGL";
		assec::Logger::CORE_LOGGER->getLogger()->info(validate);
		assec::Logger::CORE_LOGGER->getLogger()->info("	Vendor: {0}", glGetString(GL_VENDOR));
		assec::Logger::CORE_LOGGER->getLogger()->info("	Renderer: {0}", glGetString(GL_RENDERER));
		assec::Logger::CORE_LOGGER->getLogger()->info("	Version: {0}", glGetString(GL_VERSION));

	}
}