#pragma once

#include "core/Config.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace assec::graphics
{
	class Texture
	{
	public:
		struct TextureProps
		{
			uint32_t m_Width, m_Height;
			Type m_WrapType;
			glm::vec4 m_BorderColor;
			Type m_MinFilterType, m_MagFilterType, m_Internalformat, m_Format, m_Type;
			bool m_GenMipMaps, m_GenAnisotropicMaps;

		};
		virtual ~Texture() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		inline const TextureProps& getProps() { return this->m_Props; }
		uint32_t m_RendererID;
		bool const operator ==(const Texture& other) const
		{
			return this->m_RendererID == other.m_RendererID;
		}
	protected:
		Texture(const uint32_t& ID, const TextureProps& props) : m_RendererID(ID), m_Props(props) { TIME_FUNCTION; }
		virtual const uint32_t genTexture() const = 0;
		TextureProps m_Props;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() { TIME_FUNCTION; }
	protected:
		Texture2D(const uint32_t& ID, const TextureProps& props) : Texture::Texture(ID, props) { TIME_FUNCTION; }
	};
}
