#include "acpch.h"
#include "core/Core.h"
#include "OpenGLGraphicsContext.h"
#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	OpenGLGraphicsContext::OpenGLGraphicsContext() : GraphicsContext::GraphicsContext() { TIME_FUNCTION; }
	OpenGLGraphicsContext::~OpenGLGraphicsContext() { TIME_FUNCTION; }
	const void OpenGLGraphicsContext::init() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Assertion failed: {0}", "failed to initialize OpenGL");
		assec::Logger::CORE_LOGGER->getLogger()->info("successfully initlialized OpenGL: ");
		assec::Logger::CORE_LOGGER->getLogger()->info("	Vendor: {0}", glGetString(GL_VENDOR));
		assec::Logger::CORE_LOGGER->getLogger()->info("	Renderer: {0}", glGetString(GL_RENDERER));
		assec::Logger::CORE_LOGGER->getLogger()->info("	Version: {0}", glGetString(GL_VERSION));

	}
	void OpenGLGraphicsContext::setActiveTexture(unsigned int texture) const
	{
		TIME_FUNCTION;
		GLCall(glActiveTexture(GL_TEXTURE0 + texture));
	}
	const ref<VertexBuffer> OpenGLGraphicsContext::createVertexBuffer0(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexBuffer>(vertices, size, usage);
	}
	const ref<IndexBuffer> OpenGLGraphicsContext::createIndexBuffer0(const void* indices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLIndexBuffer>(indices, size, usage);
	}
	const ref<VertexArray> OpenGLGraphicsContext::createVertexArray0(VertexArray::VertexArrayData vertexArrayData) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexArray>(vertexArrayData);
	}
	const ref<VertexArray> OpenGLGraphicsContext::createVertexArray0(Type& usage, const size_t& size) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexArray>(toOpenGLType(usage), size);
	}
	const ref<Shader> OpenGLGraphicsContext::createShader0(const char* source, Type& type) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLShader>(source, type);
	}
	const ref<ShaderProgram> OpenGLGraphicsContext::createShaderProgram0(const char* vertexSource, const char* fragmentSource) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLShaderProgram>(vertexSource, fragmentSource);
	}
	const ref<Texture2D> OpenGLGraphicsContext::createTexture2D0(unsigned int width, unsigned int height, const void* data, Texture::TextureProps props) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLTexture2D>(width, height, data, props);
	}
}
