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
			Type m_MinFilterType;
			Type m_MagFilterType;
			bool m_GenMipMaps;
			bool m_GenAnisotropicMaps;
			Type m_Internalformat;
			Type m_Format;
			Type m_Type;
		};
		virtual ~Texture() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		inline const TextureProps& getProps() { return this->m_Props; }
		uint32_t m_RendererID;
	protected:
		Texture(uint32_t ID, TextureProps props) : m_RendererID(ID), m_Props(props) { TIME_FUNCTION; }
		virtual const uint32_t genTexture() const = 0;
		TextureProps m_Props;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() { TIME_FUNCTION; }
	protected:
		Texture2D(uint32_t ID, TextureProps props) : Texture::Texture(ID, props) { TIME_FUNCTION; }
	};
}
