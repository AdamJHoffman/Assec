#pragma once

#include "graphics/Buffer.h"

namespace assec::graphics
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertices, const size_t& size, const int& usage);
		OpenGLVertexBuffer(const int& usage, const size_t& size);
		~OpenGLVertexBuffer();
		virtual void addData(const void* vertices, const size_t& size, const int& usage) const override;
		virtual void addSubData(const void* data, const size_t& size, const int& offset) const override;
		virtual void bind() const override;
		virtual void cleanup() const override;
	protected:
		virtual const uint32_t genBuffer() const override;
	private:
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const void* indices, const size_t& size, const int& usage);
		OpenGLIndexBuffer(const int& usage, const size_t& size);
		~OpenGLIndexBuffer();
		virtual void addData(const void* vertices, const size_t& size, const int& usage) override;
		virtual void addSubData(const void* data, const size_t& size, const int& offset) override;
		virtual void bind() const override;
		virtual void cleanup() const override;
	protected:
		virtual const uint32_t genBuffer() const override;
	};

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferProps& frameBufferProps);
		~OpenGLFrameBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void cleanup() override;
		virtual void resize() override;
		virtual void validate() const override;
		virtual void addTextureAttachment(const Type& attachment, const Type& internalFormat, const Type& format, const Type& type) override;
	protected:
		virtual const uint32_t genBuffer(const FrameBufferProps& frameBufferProps) const override;
	};
} // assec::graphics
