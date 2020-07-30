#include "acpch.h"
#include "core/OpenGLConfig.h"
#include "graphics/openGL/OpenGLBuffer.h"
#include "OpenGLTexture.h"

namespace assec::graphics
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, const size_t& size, const int& usage) : VertexBuffer::VertexBuffer(this->genBuffer())
	{
		TIME_FUNCTION;
		this->addData(vertices, size, usage);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(const int& usage, const size_t& size) : VertexBuffer::VertexBuffer(this->genBuffer())
	{
		TIME_FUNCTION;
		this->addData(nullptr, size, usage);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer() { TIME_FUNCTION; }
	void OpenGLVertexBuffer::addData(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, usage));
	}
	void OpenGLVertexBuffer::addSubData(const void* data, const size_t& size, const int offset) const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	}
	void OpenGLVertexBuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
	}
	void OpenGLVertexBuffer::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}
	const uint32_t OpenGLVertexBuffer::genBuffer() const
	{
		TIME_FUNCTION;
		uint32_t ID;
		GLCall(glCreateBuffers(1, &ID));
		return ID;
	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(const void* indices, const size_t& size, const int& usage) : IndexBuffer::IndexBuffer(this->genBuffer(), (size / sizeof(uint32_t)))
	{
		TIME_FUNCTION;
		this->addData(indices, size, usage);
	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(const int& usage, const size_t& size) : IndexBuffer::IndexBuffer(this->genBuffer(), 0)
	{
		TIME_FUNCTION;
		this->addData(nullptr, size, usage);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer() { TIME_FUNCTION; }
	void OpenGLIndexBuffer::addData(const void* indices, const size_t& size, const int& usage)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage));
		this->m_Count = indices == nullptr ? 0 : (size / sizeof(uint32_t));
	}
	void OpenGLIndexBuffer::addSubData(const void* data, const size_t& size, const int offset)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
		this->m_Count = data == nullptr ? 0 : (size / sizeof(uint32_t));
	}
	void OpenGLIndexBuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID));
	}
	void OpenGLIndexBuffer::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}
	const uint32_t OpenGLIndexBuffer::genBuffer() const
	{
		TIME_FUNCTION;
		uint32_t ID;
		GLCall(glCreateBuffers(1, &ID));
		return ID;
	}
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferProps& frameBufferProps) : FrameBuffer(this->genBuffer(frameBufferProps), frameBufferProps)
	{
		this->bind();

		Texture::TextureProps props = { frameBufferProps.m_Width, frameBufferProps.m_Height , assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, false, false, Type::RGBA8, Type::RGBA, Type::UNSIGNED_BYTE };
		this->m_ColorTetxure = std::make_shared<OpenGLTexture2D>(nullptr, props);
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_ColorTetxure->m_RendererID, 0));

		props = { frameBufferProps.m_Width, frameBufferProps.m_Height , assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, false, false, Type::DEPTH24_STENCIL8, Type::DEPTH_STENCIL, Type::UNSIGNED_INT_24_8 };
		this->m_DepthTexture = std::make_shared<OpenGLTexture2D>(nullptr, props);
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_DepthTexture->m_RendererID, 0));

		AC_CORE_ASSERT_(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		this->unbind();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer() { TIME_FUNCTION; }
	void OpenGLFrameBuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, this->m_RendererID));
	}
	void OpenGLFrameBuffer::unbind() const
	{
		TIME_FUNCTION;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
	void OpenGLFrameBuffer::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteFramebuffers(1, &this->m_RendererID));
	}
	void OpenGLFrameBuffer::invalidate()
	{
		TIME_FUNCTION;
		this->cleanup();
		this->m_ColorTetxure->cleanup();
		this->m_DepthTexture->cleanup();
		this->m_RendererID = this->genBuffer(this->m_FrameBufferProps);

		this->bind();

		Texture::TextureProps props = { this->m_FrameBufferProps.m_Width, this->m_FrameBufferProps.m_Height , assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, false, false, Type::RGBA8, Type::RGBA, Type::UNSIGNED_BYTE };
		this->m_ColorTetxure = std::make_shared<OpenGLTexture2D>(nullptr, props);
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_ColorTetxure->m_RendererID, 0));

		props = { this->m_FrameBufferProps.m_Width, this->m_FrameBufferProps.m_Height , assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, false, false, Type::DEPTH24_STENCIL8, Type::DEPTH_STENCIL, Type::UNSIGNED_INT_24_8 };
		this->m_DepthTexture = std::make_shared<OpenGLTexture2D>(nullptr, props);
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_DepthTexture->m_RendererID, 0));

		AC_CORE_ASSERT_(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		this->unbind();
	}
	const uint32_t OpenGLFrameBuffer::genBuffer(const FrameBufferProps& frameBufferProps) const
	{
		TIME_FUNCTION;
		uint32_t ID;
		if (frameBufferProps.swapChainTarget)
		{
			ID = 0;
		}
		else
		{
			GLCall(glCreateFramebuffers(1, &ID));
		}
		return ID;
	}
}
