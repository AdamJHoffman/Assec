#pragma once

#include "core/Base.h"

#include "graphics/Texture.h"

namespace assec::graphics
{
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
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { TIME_FUNCTION; }
		virtual void addData(const void* data, CONST_REF(size_t) size, CONST_REF(int) usage) const = 0;
		virtual void addSubData(const void* data, CONST_REF(size_t) size, CONST_REF(int) offset) const = 0;
		virtual void bind() const = 0;
	protected:
		VertexBuffer(CONST_REF(uint32_t) ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const uint32_t genBuffer() const = 0;

		uint32_t m_RendererID;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { TIME_FUNCTION; }
		virtual void addData(const void* vertices, CONST_REF(size_t) size, CONST_REF(int) usage) = 0;
		virtual void addSubData(const void* data, CONST_REF(size_t) size, CONST_REF(int) offset) = 0;
		virtual void bind() const = 0;
		CONST_REF(size_t) getCount() const { return this->m_Count; }
	protected:
		IndexBuffer(CONST_REF(uint32_t) ID, CONST_REF(size_t) count) : m_RendererID(ID), m_Count(count) { TIME_FUNCTION; }
		virtual const uint32_t genBuffer() const = 0;

		uint32_t m_RendererID;
		size_t m_Count;
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
		uint32_t m_RendererID;
	protected:
		FrameBuffer(const uint32_t& ID, const FrameBufferProps& frameBufferProps) : m_RendererID(ID), m_FrameBufferProps(frameBufferProps) { TIME_FUNCTION; }
		virtual const uint32_t genBuffer(const FrameBufferProps& frameBufferProps) const = 0;
		FrameBufferProps m_FrameBufferProps;
		std::unordered_map<Type, std::shared_ptr<Texture>> m_TextureAttachments = std::unordered_map<Type, std::shared_ptr<Texture>>();
	};
} // namespace assec::graphics
