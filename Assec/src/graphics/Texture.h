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
			Type m_WrapType = Type::CLAMP_TO_EDGE, m_InternalFormat = Type::RGB8, m_DataFormat = Type::RGB, m_DataType = Type::UNSIGNED_BYTE;
			glm::vec4 m_BorderColor = glm::vec4(1.0f);
			Type m_MinFilterType = Type::LINEAR_MIPMAP_LINEAR, m_MagFilterType = Type::LINEAR;
			bool m_GenMipMaps = true, m_GenAnisotropicMaps = true;

		};
		virtual ~Texture() { TIME_FUNCTION; }

		virtual void bind() const = 0;
		virtual void setData(const void*, const uint32_t&) const = 0;
		virtual void* getData() const = 0;

		inline const TextureProps& getProps() const { return this->m_Props; }
		inline const uint32_t& getWidth() const { return this->m_Width; }
		inline const uint32_t& getHeigth() const { return this->m_Height; }
		inline const uint32_t& getNativeTexture() const { return this->m_RendererID; }

		bool const operator ==(const Texture& other) const
		{
			return this->m_RendererID == other.m_RendererID;
		}
	protected:
		Texture(const uint32_t& ID, const uint32_t& width, const uint32_t& height, const std::string& path, const TextureProps& props)
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
		Texture2D(const uint32_t& ID, const uint32_t& width, const uint32_t& height, const std::string& path, const TextureProps& props)
			: Texture::Texture(ID, width, height, path, props) { TIME_FUNCTION; }
	};
}
