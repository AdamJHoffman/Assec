#include "acpch.h"
#include "OpenGLGraphicsContext.h"
#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace assec::graphics
{
	OpenGLGraphicsContext::OpenGLGraphicsContext()
		: GraphicsContext::GraphicsContext() { TIME_FUNCTION; }
	OpenGLGraphicsContext::~OpenGLGraphicsContext() { TIME_FUNCTION; }
	const void OpenGLGraphicsContext::init() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Assertion failed: {0}", "failed to initialize OpenGL");
		int texture_units;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units));
		this->m_ContextData = { (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER),
			(const char*)glGetString(GL_VERSION), texture_units };
		AC_CORE_INFO("successfully initialized OpenGL: ");
		AC_CORE_INFO("	Vendor: {0}", this->m_ContextData.m_Vendor);
		AC_CORE_INFO("	Renderer: {0}", this->m_ContextData.m_Renderer);
		AC_CORE_INFO("	Version: {0}", this->m_ContextData.m_Version);
	}
	void OpenGLGraphicsContext::setActiveTexture(uint32_t texture) const
	{
		TIME_FUNCTION;
		GLCall(glActiveTexture(GL_TEXTURE0 + texture));
	}
	VertexBuffer* OpenGLGraphicsContext::createVertexBuffer0(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return new OpenGLVertexBuffer(vertices, size, usage);
	}
	IndexBuffer* OpenGLGraphicsContext::createIndexBuffer0(const void* indices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return new OpenGLIndexBuffer(indices, size, usage);
	}
	VertexArray* OpenGLGraphicsContext::createVertexArray0(VertexArray::VertexArrayData vertexArrayData) const
	{
		TIME_FUNCTION;
		return new OpenGLVertexArray(vertexArrayData);
	}
	VertexArray* OpenGLGraphicsContext::createVertexArray0(Type& usage, const size_t& size) const
	{
		TIME_FUNCTION;
		return new OpenGLVertexArray(toOpenGLType(usage), size);
	}
	Shader* OpenGLGraphicsContext::createShader0(const char* source, Type& type) const
	{
		TIME_FUNCTION;
		return new OpenGLShader(source, type);
	}
	ShaderProgram* OpenGLGraphicsContext::createShaderProgram0(const char* vertexSource, const char* fragmentSource) const
	{
		TIME_FUNCTION;
		return new OpenGLShaderProgram(vertexSource, fragmentSource);
	}
	Texture2D* OpenGLGraphicsContext::createTexture2D0(const void* data, Texture::TextureProps props) const
	{
		TIME_FUNCTION;
		return new OpenGLTexture2D(data, props);
	}
	FrameBuffer* OpenGLGraphicsContext::createFrameBuffer0(const FrameBuffer::FrameBufferProps& frameBufferProps) const
	{
		TIME_FUNCTION;
		return new OpenGLFrameBuffer(frameBufferProps);
	}

}
