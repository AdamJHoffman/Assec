#pragma once

#include "graphics/Buffer.h"

namespace assec::graphics
{
	class VertexArray
	{
	public:
		struct VertexArrayProps
		{
			const void* vertices, * indices;
			size_t verticesSize, indicesSize;
			uint32_t usage;
			VertexBufferLayout layout;
		};
		virtual ~VertexArray() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void render() const = 0;
		virtual void mapVertexAttributes(CONST_REF(size_t) verticesSize, CONST_REF(VertexBufferLayout) layout) const = 0;
		INLINE CONST_REF(VertexBuffer) getVertexBuffer() const { return *this->m_VertexBuffer; }
		INLINE CONST_REF(IndexBuffer) getIndexBuffer() const { return *this->m_IndexBuffer; }
		INLINE REF(VertexBuffer) getVertexBuffer() { return *this->m_VertexBuffer; }
		INLINE REF(IndexBuffer) getIndexBuffer() { return *this->m_IndexBuffer; }
	protected:
		VertexArray(CONST_REF(uint32_t) ID) : m_RendererID(ID), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr) { TIME_FUNCTION; }
		virtual const uint32_t genVertexArray() const = 0;

		uint32_t m_RendererID;
		scope<VertexBuffer> m_VertexBuffer;
		scope<IndexBuffer> m_IndexBuffer;
	};
} // namespace assec::graphics
