#include "acpch.h"
#include "core/OpenGLConfig.h"
#include "graphics/openGL/OpenGLBuffer.h"

namespace assec::graphics
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, const size_t& size, const int& usage) : VertexBuffer::VertexBuffer(this->genBuffer())
	{
		TIME_FUNCTION;
		this->addData(vertices, size, usage);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(const int& usage, const size_t& size) : VertexBuffer::VertexBuffer(this->genBuffer())
	{
		TIME_FUNCTION;
		this->addData(nullptr, size, usage);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer() { TIME_FUNCTION; }
	void OpenGLVertexBuffer::addData(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, usage));
	}
	void OpenGLVertexBuffer::addSubData(const void* data, const size_t& size, const int offset) const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	}
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
	OpenGLIndexBuffer::OpenGLIndexBuffer(const void* indices, const size_t& size, const int& usage) : IndexBuffer::IndexBuffer(this->genBuffer(), (size / sizeof(unsigned int)))
	{
		TIME_FUNCTION;
		this->addData(indices, size, usage);
	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(const int& usage, const size_t& size) : IndexBuffer::IndexBuffer(this->genBuffer(), 0)
	{
		TIME_FUNCTION;
		this->addData(nullptr, size, usage);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer() { TIME_FUNCTION; }
	void OpenGLIndexBuffer::addData(const void* indices, const size_t& size, const int& usage)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage));
		this->m_Count = indices == nullptr ? 0 : (size / sizeof(unsigned int));
	}
	void OpenGLIndexBuffer::addSubData(const void* data, const size_t& size, const int offset)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
		this->m_Count = data == nullptr ? 0 : (size / sizeof(unsigned int));
	}
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
