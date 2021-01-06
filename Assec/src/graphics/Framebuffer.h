#pragma once

#include "core/Base.h"

#include "Texture.h"

namespace assec::graphics
{
	struct RenderbufferProps
	{
		uint32_t width, height, samples = 1;
		InternalFormat internalFormat = InternalFormat::RGBA8;
	};
	class Renderbuffer
	{
	public:
		virtual void bind() const = 0;

		CONST_REF(RenderbufferProps) renderbufferProps() const { TIME_FUNCTION; return this->m_Props; }
		CONST_REF(uint32_t) native() const { TIME_FUNCTION; return this->m_RendererID; }
	protected:
		Renderbuffer(const uint32_t& ID, CONST_REF(RenderbufferProps) props) : m_RendererID(ID), m_Props(props) { TIME_FUNCTION; }
		virtual ~Renderbuffer() { TIME_FUNCTION; }
		
		virtual uint32_t createRenderbuffer() = 0;
		virtual void deleteRenderbuffer() const = 0;

		virtual void storage() const = 0;
		virtual void multisampledStorage() const = 0;

		uint32_t m_RendererID;
		RenderbufferProps m_Props;
	};
	struct FramebufferProps
	{
		uint32_t width, height, samples = 1;
		bool swapChainTarget = false;
	};
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() { TIME_FUNCTION; }
		
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void blit(CONST_REF(Framebuffer)) const = 0;

		virtual bool validate() const = 0;

		virtual void selectDrawBuffers(CONST_REF(std::vector<DrawBuffer>)) const = 0;

		virtual void resize() = 0;
		virtual void addTextureAttachment(const FrameBufferAttachment& attachment, const InternalFormat& internalFormat) = 0;
		virtual void addRenderbufferAttachment(const FrameBufferAttachment& attachment, const InternalFormat& internalFormat) = 0;

		inline CONST_REF(FramebufferProps) getFrameBufferProps() const { TIME_FUNCTION; return this->m_FrameBufferProps; }
		inline REF(FramebufferProps) getFrameBufferProps() { TIME_FUNCTION; return this->m_FrameBufferProps; }
		inline CONST_REF(Texture) getTextureAttachment(const FrameBufferAttachment& attachment) { TIME_FUNCTION; return *this->m_TextureAttachments[attachment]; }
		inline CONST_REF(Renderbuffer) getRenderbufferAttachment(const FrameBufferAttachment& attachment) { TIME_FUNCTION; return *this->m_RenderbufferAttachments[attachment]; }

	protected:
		Framebuffer(const uint32_t& ID, const FramebufferProps& frameBufferProps) : m_RendererID(ID), m_FrameBufferProps(frameBufferProps) { TIME_FUNCTION; }
		virtual uint32_t createFramebuffer(CONST_REF(bool) isSwapchainTarget) const = 0;
		virtual void deleteFramebuffer() const = 0;

		FramebufferProps m_FrameBufferProps;
		std::unordered_map<FrameBufferAttachment, std::shared_ptr<Texture>> m_TextureAttachments = std::unordered_map<FrameBufferAttachment, std::shared_ptr<Texture>>();
		std::unordered_map<FrameBufferAttachment, std::shared_ptr<Renderbuffer>> m_RenderbufferAttachments = std::unordered_map<FrameBufferAttachment, std::shared_ptr<Renderbuffer>>();

		uint32_t m_RendererID;
	};
}