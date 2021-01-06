#pragma once

#include "graphics/Buffer.h"

#include "OpenGLGraphicsContext.h"
#include <glad/glad.h>

namespace assec::graphics
{

	template<typename T> class OpenGLBuffer : public Buffer<T>
	{
	public:
		OpenGLBuffer(CONST_REF(BufferTarget) target) : Buffer<T>(this->create(), target) { TIME_FUNCTION; }
		~OpenGLBuffer() { TIME_FUNCTION;  this->destroy(); }


		virtual void bind() const override
		{
			GLCall(glBindBuffer(toOpenGLType(this->m_Target), this->native()));
		}

		virtual void data(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage) const override
		{
			GLCall(glNamedBufferData(this->native(), data.size() * sizeof(T), data.empty() ? nullptr : &data.front(), toOpenGLType(usage)));
		}
		virtual void storage(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage, CONST_REF(std::vector<BufferStorageFlag>) flags) const override
		{
			GLenum bitflag = 0;
			for (auto& flag : flags)
			{
				bitflag |= toOpenGLType(flag);
			}
			GLCall(glNamedBufferStorage(this->native(), data.size() * sizeof(T), data.empty() ? nullptr : &data.front(), bitflag));
		}
		virtual void subData(CONST_REF(std::vector<T>) data, CONST_REF(uint32_t) offset) const override
		{
			GLCall(glNamedBufferSubData(this->native(), offset, data.size() * sizeof(T), data.empty() ? nullptr : &data.front()));
		}
		virtual void clearData(CONST_REF(std::vector<T>) data, CONST_REF(Type) internalFormat,
			CONST_REF(Type) format, CONST_REF(Type) type) const override
		{
			GLCall(glClearNamedBufferData(this->native(), toOpenGLType(internalFormat), toOpenGLType(format), toOpenGLType(type), data.empty() ? nullptr : &data.front()));
		}
		virtual void clearSubData(CONST_REF(std::vector<T>) data, CONST_REF(Type) internalFormat,
			CONST_REF(Type) format, CONST_REF(Type) type, CONST_REF(uint32_t) offset) const override
		{
			GLCall(glClearNamedBufferSubData(this->native(), toOpenGLType(internalFormat), offset, data.size() * sizeof(T), toOpenGLType(format),
				toOpenGLType(type), data.empty() ? nullptr : &data.front()));
		}
		virtual void copySubData(CONST_REF(Buffer<T>) target, CONST_REF(uint32_t) readOffset,
			CONST_REF(uint32_t) writeOffset, CONST_REF(uint32_t) count) const override
		{
			GLCall(glCopyNamedBufferSubData(this->native(), target.native(), readOffset, writeOffset, count * sizeof(T)));
		}

		virtual uint32_t count() const override
		{
			int result = 0;
			GLCall(glGetNamedBufferParameteriv(this->native(), GL_BUFFER_SIZE, &result));
			return static_cast<uint32_t>(result / sizeof(T));
		}

		virtual std::vector<T> getSubData(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count) const override
		{
			std::vector<T> result = std::vector<T>(count);
			GLCall(glGetNamedBufferSubData(this->native(), offset, count * sizeof(T), &result[0]));
			return result;
		}
		virtual void invalidateData() const override
		{
			GLCall(glInvalidateBufferData(this->native()));
		}
		virtual void invalidateSubData(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count) const override
		{
			GLCall(glInvalidateBufferSubData(this->native(), offset, count * sizeof(T)));
		}
		virtual void* map(CONST_REF(Access) access) const override
		{
			GLCall(void* result = glMapNamedBuffer(this->native(), toOpenGLType(access)));
			return result;
		}
		virtual void* mapRange(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count, CONST_REF(Access) access) const override
		{
			GLCall(void* result = glMapNamedBufferRange(this->native(), offset, count * sizeof(T), toOpenGLType(access)));
			return result;
		}
		virtual bool unmap() const override
		{
			GLCall(bool result = glUnmapNamedBuffer(this->native()));
			return result;
		}
	protected:
		virtual uint32_t create() const override
		{
			uint32_t result = 0;
			GLCall(glCreateBuffers(1, &result));
			return result;
		}
		virtual void destroy() const override
		{
			GLCall(glDeleteBuffers(1, &this->native()));
		}
	};
} // assec::graphics