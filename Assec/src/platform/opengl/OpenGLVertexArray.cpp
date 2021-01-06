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
		this->m_VertexBuffer = makeScope<OpenGLBuffer<unsigned char>>(BufferTarget::ARRAY_BUFFER);
		this->m_VertexBuffer->data(std::vector<unsigned char>((unsigned char*)vertexArrayData.vertices, (unsigned char*)vertexArrayData.vertices + (vertexArrayData.verticesSize / sizeof(unsigned char))), Usage::DYNAMIC_DRAW);
		this->m_VertexBuffer->bind();
		this->mapVertexAttributes(vertexArrayData.verticesSize, vertexArrayData.layout);
		this->m_IndexBuffer = std::make_unique<OpenGLBuffer<uint32_t>>(BufferTarget::ELEMENT_ARRAY_BUFFER);
		this->m_IndexBuffer->data(std::vector<uint32_t>((uint32_t*)vertexArrayData.indices, (uint32_t*)vertexArrayData.indices + (vertexArrayData.indicesSize / sizeof(uint32_t))), Usage::DYNAMIC_DRAW);
		this->m_IndexBuffer->bind();
	}
	OpenGLVertexArray::OpenGLVertexArray(const int& usage, const size_t& size)
		: VertexArray::VertexArray(this->genVertexArray())
	{
		TIME_FUNCTION;
		this->bind();
		this->m_VertexBuffer = makeScope<OpenGLBuffer<unsigned char>>(BufferTarget::ARRAY_BUFFER);
		this->m_VertexBuffer->data(std::vector<unsigned char>(size/sizeof(unsigned char)), Usage::DYNAMIC_DRAW);
		this->m_VertexBuffer->bind();
		this->m_IndexBuffer = std::make_unique<OpenGLBuffer<uint32_t>>(BufferTarget::ELEMENT_ARRAY_BUFFER);
		this->m_IndexBuffer->data(std::vector<uint32_t>(size/sizeof(uint32_t)), Usage::DYNAMIC_DRAW);
		this->m_IndexBuffer->bind();
		//this->m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(usage, size);
		//this->m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(usage, size);
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
		this->m_VertexBuffer->bind();
		this->m_IndexBuffer->bind();
		GLCall(glDrawElements(GL_TRIANGLES, (int)this->m_IndexBuffer->count(), GL_UNSIGNED_INT, nullptr));
	}
	void OpenGLVertexArray::mapVertexAttributes(const size_t& verticesSize, const VertexBufferLayout& layout) const
	{
		TIME_FUNCTION;
		this->bind();
		this->m_VertexBuffer->bind();
		this->m_IndexBuffer->bind();
		void* pointer = 0;
		for (int i = 0; i < layout.m_Attributes.size(); i++)
		{
			auto& attrib = layout.m_Attributes[i];
			GLCall(glEnableVertexAttribArray(i));
			switch (attrib.type)
			{
			case DataType::BYTE:
			case DataType::UNSIGNED_BYTE:
			case DataType::SHORT:
			case DataType::UNSIGNED_SHORT:
			case DataType::INT:
			case DataType::UNSIGNED_INT:
				if (attrib.normalized)
				{
					GLCall(glVertexAttribPointer(i, attrib.count, toOpenGLType(attrib.type), 
						attrib.normalized, static_cast<GLsizei>(attrib.size()), pointer));
				}
				else
				{
					GLCall(glVertexAttribIPointer(i, attrib.count, toOpenGLType(attrib.type),
						static_cast<GLsizei>(attrib.size()), pointer));
				}
				break;
			case DataType::FLOAT:
				GLCall(glVertexAttribPointer(i, attrib.count, toOpenGLType(attrib.type),
					attrib.normalized, static_cast<GLsizei>(attrib.size()), pointer));
				break;
			case DataType::DOUBLE:
				GLCall(glVertexAttribLPointer(i, attrib.count, toOpenGLType(attrib.type),
					static_cast<GLsizei>(attrib.size()), pointer));
				break;
			}
			pointer = static_cast<char*>(pointer) + (verticesSize / layout.calculateVertexSize() * attrib.size());
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
