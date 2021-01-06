#pragma once

#include "core/Base.h"

#include "graphics/Texture.h"

namespace assec::graphics
{
	template<typename T> class Buffer
	{
	public:
		virtual ~Buffer() { TIME_FUNCTION; }

		virtual void bind() const = 0;

		virtual void data(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage) const = 0;
		virtual void storage(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage, CONST_REF(std::vector<BufferStorageFlag>)) const = 0;
		virtual void subData(CONST_REF(std::vector<T>) data, CONST_REF(uint32_t) offset) const = 0;
		virtual void clearData(CONST_REF(std::vector<T>) data, CONST_REF(Type) internalFormat, CONST_REF(Type) format, CONST_REF(Type) type) const = 0;
		virtual void clearSubData(CONST_REF(std::vector<T>) data, CONST_REF(Type) internalFormat, CONST_REF(Type) format, CONST_REF(Type) type, CONST_REF(uint32_t) offset) const = 0;
		virtual void copySubData(CONST_REF(Buffer<T>) target, CONST_REF(uint32_t) readOffset, CONST_REF(uint32_t) writeOffset, CONST_REF(uint32_t) count) const = 0;

		virtual uint32_t count() const = 0;

		virtual std::vector<T> getSubData(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count) const = 0;
		virtual void invalidateData() const = 0;
		virtual void invalidateSubData(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count) const = 0;
		virtual void* map(CONST_REF(Access) access) const = 0;
		virtual void* mapRange(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count, CONST_REF(Access) access) const = 0;
		virtual bool unmap() const = 0;

		CONST_REF(uint32_t) native() const { return this->m_RendererID; }
	protected:

		typedef T value;

		Buffer(CONST_REF(uint32_t) rendererID, CONST_REF(BufferTarget) target) : m_RendererID(rendererID), m_Target(target) { TIME_FUNCTION; }
		virtual uint32_t create() const = 0;
		virtual void destroy() const = 0;

		uint32_t m_RendererID;
		BufferTarget m_Target;
	};

	typedef Buffer<unsigned char> VertexBuffer;
	typedef Buffer<uint32_t> IndexBuffer;

	struct VertexBufferAttribute
	{
		const size_t size() const
		{
			TIME_FUNCTION;
			size_t result = 0;
			switch (this->type)
			{
			case DataType::BYTE:
				result = sizeof(char);
				break;
			case DataType::UNSIGNED_BYTE:
				result = sizeof(unsigned char);
				break;
			case DataType::SHORT:
				result = sizeof(short);
				break;
			case DataType::UNSIGNED_SHORT:
				result = sizeof(unsigned short);
				break;
			case DataType::INT:
				result = sizeof(int);
				break;
			case DataType::UNSIGNED_INT:
				result = sizeof(unsigned int);
				break;
			case DataType::FLOAT:
				result = sizeof(float);
				break;
			default:
				result = 0;
				break;
			}
			return result * this->count;
		}
		DataType type;
		bool normalized;
		int count;
	};
	struct VertexBufferLayout
	{
		const size_t calculateVertexSize() const
		{
			TIME_FUNCTION;
			size_t result = 0;
			for (auto attrib : this->m_Attributes)
			{
				result += attrib.size();
			}
			return result;
		}
		std::vector<VertexBufferAttribute> m_Attributes = std::vector<VertexBufferAttribute>();
	};
} // namespace assec::graphics
