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
			Type m_WrapType;
			glm::vec4 m_BorderColor;
			Type m_MinFilterType;
			Type m_MagFilterType;
			bool m_GenMipMaps;
			bool m_GenAnisotropicMaps;
		};
		virtual ~Texture() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		unsigned int m_RendererID, m_Width, m_Height;
	protected:
		Texture(unsigned int ID, unsigned int& width, unsigned int& height, TextureProps props) : m_RendererID(ID), m_Width(width), m_Height(height), m_Props(props) { TIME_FUNCTION; }
		virtual const unsigned int genTexture() const = 0;
		TextureProps m_Props;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() { TIME_FUNCTION; }
	protected:
		Texture2D(unsigned int ID, unsigned int& width, unsigned int& height, TextureProps props) : Texture::Texture(ID, width, height, props) { TIME_FUNCTION; }
	};
}
