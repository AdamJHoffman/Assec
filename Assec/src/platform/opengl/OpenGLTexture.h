#pragma once

#include <glad/glad.h>

#include "graphics/Texture.h"

namespace assec::graphics
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const uint32_t& width, const uint32_t& height, const TextureProps& props);
		OpenGLTexture2D(const std::string& path, const TextureProps& props);
		virtual ~OpenGLTexture2D();
		virtual void bind() const override;
		virtual void setData(const void*, const uint32_t&) const override;
		virtual void* getData() const override;
	protected:
		virtual const uint32_t genTexture() const override;
	};
} // assec::graphics
