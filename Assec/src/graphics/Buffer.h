#pragma once
#include "core/Config.h"

namespace assec::graphics
{
	class VertexBuffer
	{
	public:
		struct VertexBufferAttribute
		{
			VertexBufferAttribute(Type type, int count, bool normalized) : m_Type(type), m_Count(count), m_Normalized(normalized) { TIME_FUNCTION; }
			const int getSize()
			{
				TIME_FUNCTION;
				int result = 0;
				switch (this->m_Type)
				{
				case Type::FLOAT:
					result = sizeof(float);
					break;
				case Type::UNSIGNED_INT:
					result = sizeof(unsigned int);
					break;
				default:
					result = 0;
					break;
				}
				return result * this->m_Count;
			}
			Type m_Type;
			bool m_Normalized;
			int m_Count;
		};
		struct VertexBufferLayout
		{
			VertexBufferLayout() : m_Attributes(std::vector<VertexBufferAttribute>()) { TIME_FUNCTION; }
			const int calculateVertexSize()
			{
				TIME_FUNCTION;
				int result = 0;
				for (auto attrib : this->m_Attributes)
				{
					result += attrib.getSize();
				}
				return result;
			}
			std::vector<VertexBufferAttribute> m_Attributes;
		};
		virtual ~VertexBuffer() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
	protected:
		VertexBuffer(unsigned int ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const unsigned int genBuffer() const = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
		size_t m_Count;
	protected:
		IndexBuffer(unsigned int ID, const size_t& count) : m_RendererID(ID), m_Count(count) { TIME_FUNCTION; }
		virtual const unsigned int genBuffer() const = 0;
	};
}
