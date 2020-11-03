#include "acpch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "OpenGLGraphicsContext.h"
#include "OpenGLBuffer.h"

namespace assec::graphics
{
	OpenGLVertexArray::OpenGLVertexArray(const VertexArrayProps& vertexArrayData)
		: VertexArray::VertexArray(this->genVertexArray())
	{
		TIME_FUNCTION;
		this->bind();
		this->m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(vertexArrayData.vertices, vertexArrayData.verticesSize, vertexArrayData.usage);
		this->mapVertexAttributes(vertexArrayData.verticesSize, vertexArrayData.layout);
		this->m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(vertexArrayData.indices, vertexArrayData.indicesSize, vertexArrayData.usage);
	}
	OpenGLVertexArray::OpenGLVertexArray(const int& usage, const size_t& size)
		: VertexArray::VertexArray(this->genVertexArray())
	{
		TIME_FUNCTION;
		this->bind();
		this->m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(usage, size);
		this->m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(usage, size);
	}
	OpenGLVertexArray::~OpenGLVertexArray() 
	{ 
		TIME_FUNCTION; 
		GLCall(glDeleteVertexArrays(1, &this->m_RendererID));
	}
	void OpenGLVertexArray::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindVertexArray(this->m_RendererID));
	}
	void OpenGLVertexArray::render() const
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glDrawElements(GL_TRIANGLES, (int)this->m_IndexBuffer->m_Count, GL_UNSIGNED_INT, nullptr));
	}
	void OpenGLVertexArray::mapVertexAttributes(const size_t& verticesSize, const VertexBuffer::VertexBufferLayout& layout) const
	{
		TIME_FUNCTION;
		this->bind();
		void* pointer = 0;
		for (int i = 0; i < layout.m_Attributes.size(); i++)
		{
			auto& attrib = layout.m_Attributes[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, attrib.m_Count, toOpenGLType(attrib.m_Type), attrib.m_Normalized, static_cast<GLsizei>(attrib.getSize()), pointer));
			pointer = static_cast<char*>(pointer) + (verticesSize / layout.calculateVertexSize() * attrib.getSize());
		}
	}
	const uint32_t OpenGLVertexArray::genVertexArray() const
	{
		TIME_FUNCTION;
		uint32_t ID;
		GLCall(glCreateVertexArrays(1, &ID));
		return ID;
	}
} // assec::graphics
