#pragma once
#include "graphics/Buffer.h"

namespace assec::graphics
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertices, const size_t& size, const int& usage);
		~OpenGLVertexBuffer();
		virtual void bind() const override;
		virtual void cleanup() const override;
	protected:
		virtual const unsigned int genBuffer() const override;
	private:
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const void* indices, const size_t& size, const int& usage);
		~OpenGLIndexBuffer();
		virtual void bind() const override;
		virtual void cleanup() const override;
	protected:
		virtual const unsigned int genBuffer() const override;
	};
}
