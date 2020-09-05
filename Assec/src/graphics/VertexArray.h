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
			const size_t verticesSize, indicesSize;
			const uint32_t usage;
			VertexBuffer::VertexBufferLayout& layout;
		};
		virtual ~VertexArray() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void render() const = 0;
		virtual void cleanup() const = 0;
		virtual void mapVertexAttributes(const size_t& verticesSize, const VertexBuffer::VertexBufferLayout& layout) const = 0;
		uint32_t m_RendererID;
		scope<VertexBuffer> m_VertexBuffer;
		scope<IndexBuffer> m_IndexBuffer;
	protected:
		VertexArray(int ID) : m_RendererID(ID), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr) { TIME_FUNCTION; }
		virtual const uint32_t genVertexArray() const = 0;
	};
}
