#pragma once

#include "graphics/VertexArray.h"

namespace assec::graphics
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(const VertexArrayProps& vertexArrayData);
		OpenGLVertexArray(const int& usage, const size_t& size);
		virtual ~OpenGLVertexArray();
		void bind() const override;
		void render() const override;
		virtual void mapVertexAttributes(const size_t& verticesSize, const VertexBuffer::VertexBufferLayout& layout) const override;
	protected:
		const uint32_t genVertexArray() const override;
	};
} // assec::graphics
