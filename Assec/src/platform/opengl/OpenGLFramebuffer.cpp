#include "acpch.h"

#include <glad/glad.h>

#include "OpenGLFramebuffer.h"
#include "OpenGLGraphicsContext.h"
#include "OpenGLTexture.h"

#include "util/misc.h"

namespace assec::graphics
{
	void OpenGLRenderbuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, this->m_RendererID));
	}

	uint32_t OpenGLRenderbuffer::createRenderbuffer()
	{
		TIME_FUNCTION;
		uint32_t result = 0;
		GLCall(glCreateRenderbuffers(1, &result));
		return result;
	}
	void OpenGLRenderbuffer::deleteRenderbuffer() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteRenderbuffers(1, &this->m_RendererID));
	}

	void OpenGLRenderbuffer::storage() const
	{
		TIME_FUNCTION;
		GLCall(glNamedRenderbufferStorage(this->m_RendererID, toOpenGLType(this->m_Props.internalFormat), this->m_Props.width, this->m_Props.height));
	}
	void OpenGLRenderbuffer::multisampledStorage() const
	{
		TIME_FUNCTION;
		GLCall(glNamedRenderbufferStorageMultisample(this->m_RendererID, this->m_Props.samples, toOpenGLType(this->m_Props.internalFormat), 
			this->m_Props.width, this->m_Props.height));
	}

	OpenGLFramebuffer::OpenGLFramebuffer(CONST_REF(FramebufferProps) frameBufferProps) 
		: Framebuffer(this->createFramebuffer(frameBufferProps.swapChainTarget), frameBufferProps) {}
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		TIME_FUNCTION;
		this->deleteFramebuffer();
	}
	void OpenGLFramebuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, this->m_RendererID));

		int drawTargetCount = 0;
		std::vector<GLenum> buffers;
		for (auto& key : util::Keys(this->m_TextureAttachments))
		{
			if (key != FrameBufferAttachment::DEPTH_ATTACHMENT && key != FrameBufferAttachment::STENCIL_ATTACHMENT
				&& key != FrameBufferAttachment::DEPTH_STENCIL_ATTACHMENT)
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
		GLCall(glViewport(0, 0, this->m_FrameBufferProps.width, this->m_FrameBufferProps.height));
	}
	void OpenGLFramebuffer::unbind() const
	{
		TIME_FUNCTION;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GLCall(glViewport(0, 0, this->m_PreviousViewportSize.x, this->m_PreviousViewportSize.y));
	}

	void OpenGLFramebuffer::blit(CONST_REF(Framebuffer) target) const
	{
	}

	void OpenGLFramebuffer::selectDrawBuffers(CONST_REF(std::vector<DrawBuffer>) drawbuffers) const
	{
		std::vector<GLenum> buffers;
		for (auto& buffer : drawbuffers)
		{
			buffers.push_back(toOpenGLType(buffer));
		}
		glDrawBuffers(static_cast<GLsizei>(drawbuffers.size()), &buffers[0]);

	}

	void OpenGLFramebuffer::addRenderbufferAttachment(const FrameBufferAttachment& attachment, const InternalFormat& internalFormat)
	{
		this->bind();
		this->m_RenderbufferAttachments[attachment] = makeRef<OpenGLRenderbuffer>(RenderbufferProps{this->m_FrameBufferProps.width, this->m_FrameBufferProps.height,
			this->m_FrameBufferProps.samples, internalFormat});
		GLCall(glNamedFramebufferRenderbuffer(this->m_RendererID, toOpenGLType(attachment), GL_RENDERBUFFER,
			this->m_RenderbufferAttachments[attachment]->native()));
		this->unbind();
	}

	void OpenGLFramebuffer::resize()
	{
		TIME_FUNCTION;
		this->deleteFramebuffer();
		this->m_RendererID = this->createFramebuffer(this->m_FrameBufferProps.swapChainTarget);
		for (auto key : util::Keys(this->m_TextureAttachments))
		{
			const FrameBufferAttachment& attachment = key;
			const InternalFormat& internalForamat = this->m_TextureAttachments.at(key)->getProps().internalFormat;
			const Format& dataFormat = this->m_TextureAttachments.at(key)->getProps().dataFormat;
			const DataType& dataType = this->m_TextureAttachments.at(key)->getProps().dataType;
			this->addTextureAttachment(attachment, internalForamat);
		}
		for (auto key : util::Keys(this->m_RenderbufferAttachments))
		{
			const FrameBufferAttachment& attachment = key;
			const InternalFormat& internalForamat = this->m_RenderbufferAttachments.at(key)->renderbufferProps().internalFormat;
			this->addRenderbufferAttachment(attachment, internalForamat);
		}
		this->validate();
	}
	bool OpenGLFramebuffer::validate() const
	{
		this->bind();
		GLCall(bool result = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE));
		this->unbind();
		return result;
	}
	void OpenGLFramebuffer::addTextureAttachment(const FrameBufferAttachment& attachment, const InternalFormat& internalFormat)
	{
		this->bind();
		this->m_TextureAttachments[attachment] = std::make_shared<OpenGLTexture2D>(this->m_FrameBufferProps.width, 
			this->m_FrameBufferProps.height, Texture::TextureProps{ assec::Type::CLAMP_TO_EDGE, 
			internalFormat, determineFormat(internalFormat), determineDataType(internalFormat), glm::vec4(1.0), assec::Type::LINEAR, assec::Type::LINEAR, false, false });
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, toOpenGLType(attachment), GL_TEXTURE_2D, 
			this->m_TextureAttachments[attachment]->getNativeTexture(), 0));
		this->unbind();
	}

	uint32_t OpenGLFramebuffer::createFramebuffer(CONST_REF(bool) isSwapchainTarget) const
	{
		TIME_FUNCTION;
		uint32_t ID;
		if (isSwapchainTarget)
		{
			ID = 0;
		}
		else
		{
			GLCall(glCreateFramebuffers(1, &ID));
		}
		return ID;
	}

	void OpenGLFramebuffer::deleteFramebuffer() const
	{
		GLCall(glDeleteFramebuffers(1, &this->m_RendererID));
	}

}