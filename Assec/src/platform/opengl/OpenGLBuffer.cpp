#include "acpch.h"

#include "OpenGLBuffer.h"

#include <glad/glad.h>

#include "OpenGLGraphicsContext.h"
#include "OpenGLTexture.h"

#include "graphics/WindowManager.h"

namespace assec::graphics
{
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

		int drawTargetCount = 0;
		std::vector<GLenum> buffers;
		for (auto& key : util::Keys(this->m_TextureAttachments))
		{
			if (key != Type::DEPTH_STENCIL_ATTACHMENT)
			{
				++drawTargetCount;
				buffers.push_back(toOpenGLType(key));
			}
		}
		if (!buffers.empty())
		{
			glDrawBuffers(drawTargetCount, &buffers[0]);
		}

		int viewportsize[4];
		GLCall(glGetIntegerv(GL_VIEWPORT, viewportsize));
		this->m_PreviousViewportSize.x = viewportsize[2];
		this->m_PreviousViewportSize.y = viewportsize[3];
		GLCall(glViewport(0, 0, this->m_FrameBufferProps.m_Width, this->m_FrameBufferProps.m_Height));
	}
	void OpenGLFrameBuffer::unbind() const
	{
		TIME_FUNCTION;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GLCall(glViewport(0, 0, this->m_PreviousViewportSize.x, this->m_PreviousViewportSize.y));
	}
	void OpenGLFrameBuffer::resize()
	{
		TIME_FUNCTION;
		GLCall(glDeleteFramebuffers(1, &this->m_RendererID));
		this->m_RendererID = this->genBuffer(this->m_FrameBufferProps);
		for (auto key : util::Keys(this->m_TextureAttachments))
		{
			const Type& attachment = key;
			const Type& internalForamat = this->m_TextureAttachments.at(key)->getProps().internalFormat;
			const Type& dataFormat = this->m_TextureAttachments.at(key)->getProps().dataFormat;
			const Type& dataType = this->m_TextureAttachments.at(key)->getProps().dataType;
			this->addTextureAttachment(attachment, internalForamat, dataFormat, dataType);
		}
		this->validate();
	}
	void OpenGLFrameBuffer::validate() const
	{
		this->bind();
		GLCall(bool result = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE));
		AC_ASSERT(result, ("framebuffer {0} incomplete", this->m_RendererID));
		this->unbind();
	}
	void OpenGLFrameBuffer::addTextureAttachment(const Type& attachment, const Type& internalFormat, const Type& dataFormat, const Type& dataType)
	{
		this->bind();
		this->m_TextureAttachments[attachment] = std::make_shared<OpenGLTexture2D>(this->m_FrameBufferProps.m_Width, this->m_FrameBufferProps.m_Height, Texture::TextureProps{ assec::Type::CLAMP_TO_EDGE, internalFormat, dataFormat, dataType, glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, false, false });
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, toOpenGLType(attachment), GL_TEXTURE_2D, this->m_TextureAttachments[attachment]->getNativeTexture(), 0));
		this->unbind();
	}
	void OpenGLFrameBuffer::clear(glm::vec4 color) const
	{
		this->bind();
		glClearColor(color.r, color.g, color.g, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->unbind();
	}



	uint32_t OpenGLFrameBuffer::pixelData(CONST_REF(glm::vec2) pos) const
	{
		this->bind();
		glReadBuffer(GL_COLOR_ATTACHMENT1);
		uint32_t result = 0;
		glReadPixels(pos.x, pos.y, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &result);
		this->unbind();
		return result;
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
