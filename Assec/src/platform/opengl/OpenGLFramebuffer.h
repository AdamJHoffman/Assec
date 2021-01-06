#pragma once

#include "graphics/Framebuffer.h"

namespace assec::graphics
{
	class OpenGLRenderbuffer : public Renderbuffer
	{
	public:
		OpenGLRenderbuffer(CONST_REF(RenderbufferProps) props) 
			: Renderbuffer(this->createRenderbuffer(), props) 
		{ 
			TIME_FUNCTION; 
			if (this->m_Props.samples > 1)
			{
				this->multisampledStorage();
			}
			else
			{
				this->storage();
			}
		}
		~OpenGLRenderbuffer() { TIME_FUNCTION; this->deleteRenderbuffer(); }

		virtual void bind() const override;
	protected:

		virtual uint32_t createRenderbuffer() override;
		virtual void deleteRenderbuffer() const override;

		virtual void storage() const override;
		virtual void multisampledStorage() const override;
	};

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(CONST_REF(FramebufferProps));
		~OpenGLFramebuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void blit(CONST_REF(Framebuffer)) const override;

		virtual bool validate() const override;

		virtual void selectDrawBuffers(CONST_REF(std::vector<DrawBuffer>)) const override;

		virtual void resize() override;
		virtual void addTextureAttachment(const FrameBufferAttachment& attachment, const InternalFormat& internalFormat) override;
		virtual void addRenderbufferAttachment(const FrameBufferAttachment& attachment, const InternalFormat& internalFormat) override;

	protected:
		virtual uint32_t createFramebuffer(CONST_REF(bool) isSwapchainTarget) const override;
		virtual void deleteFramebuffer() const override;
	private:
		mutable glm::vec<2, int> m_PreviousViewportSize = glm::vec<2, int>(0);
	};
}