#pragma once
#include "core/Config.h"

namespace assec::graphics
{
	class VertexBuffer
	{
	public:
		struct VertexBufferAttribute
		{
			VertexBufferAttribute(DataType type, int count, bool normalized) : m_Type(type), m_Count(count), m_Normalized(normalized) {}
			const int getSize()
			{
				switch (this->m_Type)
				{
				case DataType::FLOAT:
					return sizeof(float);
					break;
				case DataType::UNSIGNED_INT:
					return sizeof(unsigned int);
					break;
				default:
					return 0;
					break;
				}
			}
			DataType m_Type;
			bool m_Normalized;
			int m_Count;
		};
		struct VertexBufferLayout
		{
			VertexBufferLayout() : m_Attributes(std::vector<VertexBufferAttribute>()) {}
			const int calculateStride() const
			{
				int stride = 0;
				for (auto attribute : this->m_Attributes)
				{
					stride += attribute.getSize() * attribute.m_Count;
				}
				return stride;
			}
			std::vector<VertexBufferAttribute> m_Attributes;
		};
		virtual ~VertexBuffer() {}
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
	protected:
		VertexBuffer(unsigned int ID) : m_RendererID(ID) {}
		virtual const unsigned int genBuffer() const = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
	protected:
		IndexBuffer(unsigned int ID) : m_RendererID(ID) {}
		virtual const unsigned int genBuffer() const = 0;
	};
}
