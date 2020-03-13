#pragma once
#include "graphics/openGL/OpenGLBuffer.h"

namespace assec::graphics
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(const void* vertices, const size_t& verticesSize, const void* indices, const size_t& indicesSize, const int& usage, graphics::VertexBuffer::VertexBufferLayout& layout);
		virtual ~OpenGLVertexArray();
		void bind() const override;
		void render() const override;
		virtual void cleanup() const override;
	protected:
		const unsigned int genVertexArray() const override;
	private:
	};
}
