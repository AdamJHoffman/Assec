#pragma once

#include "graphics/Buffer.h"

#include "OpenGLGraphicsContext.h"
#include <glad/glad.h>

namespace assec::graphics
{

	template<typename T> class OpenGLBuffer : public Buffer<T>
	{
	public:
		OpenGLBuffer(CONST_REF(BufferTarget) target) : Buffer<T>(this->createBuffer(), target) { TIME_FUNCTION; }
		~OpenGLBuffer() { TIME_FUNCTION;  this->deleteBuffer(); }


		virtual void bind() const override
		{
			GLCall(glBindBuffer(toOpenGLType(this->m_Target), this->m_RendererID));
		}

		virtual void data(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage) const override
		{
			GLCall(glNamedBufferData(this->m_RendererID, data.size() * sizeof(T), data.empty() ? nullptr : &data.front(), toOpenGLType(usage)));
		}
		// Immutable TODO flags
		virtual void storage(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage) const override
		{
			GLCall(glNamedBufferStorage(this->m_RendererID, data.size() * sizeof(T), data.empty() ? nullptr : &data.front(), 0));
		}
		virtual void subData(CONST_REF(std::vector<T>) data, CONST_REF(uint32_t) offset) const override
		{
			int size = sizeof(T) * data.size();
			uint32_t ssize = this->count() * sizeof(T);
			GLCall(glNamedBufferSubData(this->m_RendererID, offset, data.size() * sizeof(T), data.empty() ? nullptr : &data.front()));
		}
		virtual void clearData(CONST_REF(std::vector<T>) data, CONST_REF(Type) internalFormat,
			CONST_REF(Type) format, CONST_REF(Type) type) const override
		{
			GLCall(glClearNamedBufferData(this->m_RendererID, toOpenGLType(internalFormat), toOpenGLType(format), toOpenGLType(type), data.empty() ? nullptr : &data.front()));
		}
		virtual void clearSubData(CONST_REF(std::vector<T>) data, CONST_REF(Type) internalFormat,
			CONST_REF(Type) format, CONST_REF(Type) type, CONST_REF(uint32_t) offset) const override
		{
			GLCall(glClearNamedBufferSubData(this->m_RendererID, toOpenGLType(internalFormat), offset, data.size() * sizeof(T), toOpenGLType(format),
				toOpenGLType(type), data.empty() ? nullptr : &data.front()));
		}
		virtual void copySubData(CONST_REF(Buffer<T>) target, CONST_REF(uint32_t) readOffset,
			CONST_REF(uint32_t) writeOffset, CONST_REF(uint32_t) count) const override
		{
			GLCall(glCopyNamedBufferSubData(this->m_RendererID, target.native(), readOffset, writeOffset, count * sizeof(T)));
		}

		virtual uint32_t count() const override
		{
			int result = 0;
			GLCall(glGetNamedBufferParameteriv(this->m_RendererID, GL_BUFFER_SIZE, &result));
			return static_cast<uint32_t>(result / sizeof(T));
		}

		virtual std::vector<T> getSubData(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count) const override
		{
			std::vector<T> result = std::vector<T>(count);
			GLCall(glGetNamedBufferSubData(this->m_RendererID, offset, count * sizeof(T), &result[0]));
			return result;
		}
		virtual void invalidateData() const override
		{
			GLCall(glInvalidateBufferData(this->m_RendererID));
		}
		virtual void invalidateSubData(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count) const override
		{
			GLCall(glInvalidateBufferSubData(this->m_RendererID, offset, count * sizeof(T)));
		}
		virtual void* map(CONST_REF(Access) access) const override
		{
			GLCall(void* result = glMapNamedBuffer(this->m_RendererID, toOpenGLType(access)));
			return result;
		}
		virtual void* mapRange(CONST_REF(uint32_t) offset, CONST_REF(uint32_t) count, CONST_REF(Access) access) const override
		{
			GLCall(void* result = glMapNamedBufferRange(this->m_RendererID, offset, count * sizeof(T), toOpenGLType(access)));
			return result;
		}
		virtual bool unmap() const override
		{
			GLCall(bool result = glUnmapNamedBuffer(this->m_RendererID));
			return result;
		}
	protected:
		virtual const uint32_t createBuffer() const override
		{
			uint32_t result = 0;
			GLCall(glCreateBuffers(1, &result));
			return result;
		}
		virtual void deleteBuffer() const override
		{
			GLCall(glDeleteBuffers(1, &this->m_RendererID));
		}
	};

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferProps& frameBufferProps);
		~OpenGLFrameBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void resize() override;
		virtual void validate() const override;
		virtual void addTextureAttachment(const Type& attachment, const Type& internalFormat, const Type& format, const Type& type) override;
		virtual void clear(glm::vec4 color) const override;

		virtual uint32_t pixelData(CONST_REF(glm::vec2) pos) const override;

	protected:
		virtual const uint32_t genBuffer(const FrameBufferProps& frameBufferProps) const override;
	private:
		mutable glm::vec<2, int> m_PreviousViewportSize = glm::vec<2, int>(0);
	};
} // assec::graphics