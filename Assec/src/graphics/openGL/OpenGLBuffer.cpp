#include "acpch.h"
#include "core/OpenGLConfig.h"
#include "graphics/openGL/OpenGLBuffer.h"

namespace assec::graphics
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, const size_t& size, const int& usage) : VertexBuffer::VertexBuffer(this->genBuffer())
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, usage));
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer() { TIME_FUNCTION; }
	void OpenGLVertexBuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
	}
	void OpenGLVertexBuffer::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}
	const unsigned int OpenGLVertexBuffer::genBuffer() const
	{
		TIME_FUNCTION;
		unsigned int ID;
		GLCall(glCreateBuffers(1, &ID));
		return ID;
	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(const void* indices, const size_t& size, const int& usage) : IndexBuffer::IndexBuffer(this->genBuffer(), size)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage));
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer() { TIME_FUNCTION; }
	void OpenGLIndexBuffer::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID));
	}
	void OpenGLIndexBuffer::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}
	const unsigned int OpenGLIndexBuffer::genBuffer() const
	{
		TIME_FUNCTION;
		unsigned int ID;
		GLCall(glCreateBuffers(1, &ID));
		return ID;
	}
}
