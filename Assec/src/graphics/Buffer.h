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
		// Immutable
		virtual void storage(CONST_REF(std::vector<T>) data, CONST_REF(Usage) usage) const = 0;
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
		virtual const uint32_t createBuffer() const = 0;
		virtual void deleteBuffer() const = 0;

		uint32_t m_RendererID;
		BufferTarget m_Target;
	};

	typedef Buffer<unsigned char> VertexBuffer;
	typedef Buffer<uint32_t> IndexBuffer;

	struct VertexBufferAttribute
	{
		VertexBufferAttribute(CONST_REF(Type) type, CONST_REF(int) count, CONST_REF(bool) normalized) : m_Type(type), m_Count(count), m_Normalized(normalized) { TIME_FUNCTION; }
		const size_t getSize() const
		{
			TIME_FUNCTION;
			size_t result = 0;
			switch (this->m_Type)
			{
			case Type::FLOAT:
				result = sizeof(float);
				break;
			case Type::UNSIGNED_INT:
				result = sizeof(uint32_t);
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
		VertexBufferLayout() { TIME_FUNCTION; }
		VertexBufferLayout(CONST_REF(std::vector<VertexBufferAttribute>) attributes) : m_Attributes(attributes) { TIME_FUNCTION; }
		const size_t calculateVertexSize() const
		{
			TIME_FUNCTION;
			size_t result = 0;
			for (auto attrib : this->m_Attributes)
			{
				result += attrib.getSize();
			}
			return result;
		}
		std::vector<VertexBufferAttribute> m_Attributes = std::vector<VertexBufferAttribute>();
	};
	
	class FrameBuffer
	{
	public:
		struct FrameBufferFormat
		{

		};
		struct FrameBufferProps
		{
			FrameBufferFormat format;
			uint32_t m_Width, m_Height, m_Samples = 1;
			bool swapChainTarget = false;
		};
		virtual ~FrameBuffer() { TIME_FUNCTION; }
		inline const FrameBufferProps& getFrameBufferProps() const { TIME_FUNCTION; return this->m_FrameBufferProps; }
		inline FrameBufferProps& getFrameBufferProps() { TIME_FUNCTION; return this->m_FrameBufferProps; }
		inline const Texture& getTextureAttachment(const Type& attachment) { TIME_FUNCTION; return *this->m_TextureAttachments[attachment]; }
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void resize() = 0;
		virtual void validate() const = 0;
		virtual void addTextureAttachment(const Type& attachment, const Type& internalFormat, const Type& format, const Type& type) = 0;
		virtual void clear(glm::vec4 color) const = 0;


		virtual uint32_t pixelData(CONST_REF(glm::vec2) pos) const = 0;

		uint32_t m_RendererID;
	protected:
		FrameBuffer(const uint32_t& ID, const FrameBufferProps& frameBufferProps) : m_RendererID(ID), m_FrameBufferProps(frameBufferProps) { TIME_FUNCTION; }
		virtual const uint32_t genBuffer(const FrameBufferProps& frameBufferProps) const = 0;
		FrameBufferProps m_FrameBufferProps;
		std::unordered_map<Type, std::shared_ptr<Texture>> m_TextureAttachments = std::unordered_map<Type, std::shared_ptr<Texture>>();
	};
} // namespace assec::graphics
