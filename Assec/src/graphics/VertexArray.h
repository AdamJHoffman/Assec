#pragma once
#include "graphics/Buffer.h"

namespace assec::graphics
{
	class VertexArray
	{
	public:
		struct VertexArrayData
		{
			const void* vertices, * indices;
			const size_t& verticesSize, indicesSize;
			const unsigned int& usage;
			VertexBuffer::VertexBufferLayout& layout;
		};
		virtual ~VertexArray() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void render() const = 0;
		virtual void cleanup() const = 0;
		virtual void mapVertexAttributes(const size_t& verticesSize, VertexBuffer::VertexBufferLayout& layout) const = 0;
		unsigned int m_RendererID;
		scope<VertexBuffer> m_VertexBuffer;
		scope<IndexBuffer> m_IndexBuffer;
	protected:
		VertexArray(int ID) : m_RendererID(ID), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr) { TIME_FUNCTION; }
		virtual const unsigned int genVertexArray() const = 0;
	};
}
