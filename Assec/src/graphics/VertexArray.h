#pragma once
#include "graphics/Buffer.h"

namespace assec::graphics
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		virtual void bind() const = 0;
		virtual void render() const = 0;
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
	protected:
		VertexArray(int ID) : m_RendererID(ID), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr) {}
		virtual const unsigned int genVertexArray() const = 0;
		scope<VertexBuffer> m_VertexBuffer;
		scope<IndexBuffer> m_IndexBuffer;
	};
}
