#include "acpch.h"
#include "core/OpenGLConfig.h"
#include "OpenGLVertexArray.h"

namespace assec::graphics
{
	OpenGLVertexArray::OpenGLVertexArray(const void* vertices, const size_t& verticesSize, const void* indices, const size_t& indicesSize, const int& usage, graphics::VertexBuffer::VertexBufferLayout& layout)
		: VertexArray::VertexArray(this->genVertexArray())
	{
		this->bind();
		this->m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(vertices, verticesSize, usage);
		int pointer = 0;
		for (unsigned int i = 0; i < layout.m_Attributes.size(); i++)
		{
			auto& attrib = layout.m_Attributes[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, attrib.m_Count, toOpenGLType(attrib.m_Type), attrib.m_Normalized, layout.calculateStride(), (const void*)pointer));
			pointer += attrib.m_Count * attrib.getSize();
		}
		this->m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(indices, indicesSize, usage);
	}
	OpenGLVertexArray::~OpenGLVertexArray() {}
	void OpenGLVertexArray::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindVertexArray(this->m_RendererID));
	}
	void OpenGLVertexArray::render() const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
	}
	void OpenGLVertexArray::cleanup() const
	{
		TIME_FUNCTION;
		this->m_VertexBuffer->cleanup();
		this->m_VertexBuffer->cleanup();
		GLCall(glDeleteVertexArrays(1, &this->m_RendererID));
	}
	const unsigned int OpenGLVertexArray::genVertexArray() const
	{
		TIME_FUNCTION;
		unsigned int ID;
		GLCall(glGenVertexArrays(1, &ID));
		return ID;
	}
}
