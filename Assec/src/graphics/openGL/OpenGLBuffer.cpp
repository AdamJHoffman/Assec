#include "acpch.h"

#include "graphics/openGL/OpenGLBuffer.h"

#include <glad/glad.h>

#include "OpenGLGraphicsContext.h"
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
	OpenGLVertexBuffer::~OpenGLVertexBuffer() 
	{
		TIME_FUNCTION;
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}
	void OpenGLVertexBuffer::addData(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, usage));
	}
	void OpenGLVertexBuffer::addSubData(const void* data, const size_t& size, const int& offset) const
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
	OpenGLIndexBuffer::~OpenGLIndexBuffer() 
	{ 
		TIME_FUNCTION; 
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}
	void OpenGLIndexBuffer::addData(const void* indices, const size_t& size, const int& usage)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage));
		this->m_Count = indices == nullptr ? 0 : (size / sizeof(uint32_t));
	}
	void OpenGLIndexBuffer::addSubData(const void* data, const size_t& size, const int& offset)
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
	const uint32_t OpenGLIndexBuffer::genBuffer() const
	{
		TIME_FUNCTION;
		uint32_t ID;
		GLCall(glCreateBuffers(1, &ID));
		return ID;
	}
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferProps& frameBufferProps) : FrameBuffer(this->genBuffer(frameBufferProps), frameBufferProps) {}
	OpenGLFrameBuffer::~OpenGLFrameBuffer() 
	{ 
		TIME_FUNCTION; 
		this->m_TextureAttachments.clear();
		GLCall(glDeleteFramebuffers(1, &this->m_RendererID));
	}
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
	void OpenGLFrameBuffer::resize()
	{
		TIME_FUNCTION;
		GLCall(glDeleteFramebuffers(1, &this->m_RendererID));
		this->m_RendererID = this->genBuffer(this->m_FrameBufferProps);
		for (auto key : util::Keys(this->m_TextureAttachments))
		{
			const Type& attachment = key;
			const Type& internalForamat = this->m_TextureAttachments.at(key)->getProps().m_Internalformat;
			const Type& format = this->m_TextureAttachments.at(key)->getProps().m_Format;
			const Type& type = this->m_TextureAttachments.at(key)->getProps().m_Type;
			this->addTextureAttachment(attachment, internalForamat, format, type);
		}
		this->validate();
	}
	void OpenGLFrameBuffer::validate() const
	{
		this->bind();
		GLCall(bool result = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE));
		AC_CLIENT_ASSERT(result, "framebuffer {0} incomplete", this->m_RendererID);
		this->unbind();
	}
	void OpenGLFrameBuffer::addTextureAttachment(const Type& attachment, const Type& internalFormat, const Type& format, const Type& type)
	{
		this->bind();
		this->m_TextureAttachments[attachment] = std::make_shared<OpenGLTexture2D>(nullptr, Texture::TextureProps{ this->m_FrameBufferProps.m_Width, this->m_FrameBufferProps.m_Height , assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, internalFormat, format, type, false, false });
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, toOpenGLType(attachment), GL_TEXTURE_2D, this->m_TextureAttachments[attachment]->m_RendererID, 0));
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
} // assec::graphics
