#pragma once
#include "graphics/Texture.h"

namespace assec::graphics
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const void* data, const TextureProps& props);
		virtual ~OpenGLTexture2D();
		virtual void bind() const override;
		virtual void cleanup() const override;
	protected:
		virtual const uint32_t genTexture() const override;
	};
} // assec::graphics
