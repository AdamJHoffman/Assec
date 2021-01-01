#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Base.h"
#include "core/KeyCode.h"

namespace assec::graphics
{
	class Texture
	{
	public:
		struct TextureProps
		{
			Type wrapType = Type::CLAMP_TO_EDGE, internalFormat = Type::RGBA8, dataFormat = Type::RGBA, dataType = Type::UNSIGNED_BYTE;
			glm::vec4 borderColor = glm::vec4(1.0f);
			Type minFilterType = Type::LINEAR_MIPMAP_LINEAR, magFilterType = Type::LINEAR;
			bool genMipMaps = true, genAnisotropicMaps = true;

		};
		virtual ~Texture() { TIME_FUNCTION; }

		virtual void bind() const = 0;
		virtual void setData(const void*, const uint32_t&) const = 0;
		virtual void* getData() const = 0;
		virtual void clear() const = 0;

		inline const TextureProps& getProps() const { TIME_FUNCTION; return this->m_Props; }
		inline const uint32_t& getWidth() const { TIME_FUNCTION; return this->m_Width; }
		inline const uint32_t& getHeigth() const { TIME_FUNCTION; return this->m_Height; }
		inline const uint32_t& getNativeTexture() const { TIME_FUNCTION; return this->m_RendererID; }

		bool const operator ==(CONST_REF(Texture) other) const
		{
			TIME_FUNCTION;
			return this->m_RendererID == other.m_RendererID;
		}
	protected:
		Texture(CONST_REF(uint32_t) ID, CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(std::string) path, CONST_REF(TextureProps) props)
			: m_RendererID(ID), m_Width(width), m_Height(height), m_Path(path), m_Props(props) { TIME_FUNCTION; }
		virtual const uint32_t genTexture() const = 0;

		TextureProps m_Props;
		uint32_t m_RendererID, m_Width, m_Height;
		std::string m_Path;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() { TIME_FUNCTION; }
	protected:
		Texture2D(CONST_REF(uint32_t) ID, CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(std::string) path, CONST_REF(TextureProps) props)
			: Texture::Texture(ID, width, height, path, props) { TIME_FUNCTION; }
	};
} // namespace assec::graphics
