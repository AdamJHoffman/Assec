#pragma once
#include "graphics/GraphicsContext.h"
#include "core/OpenGLConfig.h"

namespace assec::graphics
{
	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext();
		virtual ~OpenGLGraphicsContext();
		virtual const void init() const override;
		virtual void setActiveTexture(uint32_t texture) const override;
		virtual int getMaxTextures() const override;
		virtual VertexBuffer* createVertexBuffer0(const void* vertices, const size_t& size, const int& usage) const override;
		virtual IndexBuffer* createIndexBuffer0(const void* indices, const size_t& size, const int& usage) const override;
		virtual VertexArray* createVertexArray0(VertexArray::VertexArrayData vertexArrayData) const override;
		virtual VertexArray* createVertexArray0(Type& usage, const size_t& size) const override;
		virtual Shader* createShader0(const char* source, Type& type) const override;
		virtual ShaderProgram* createShaderProgram0(const char* vertexSource, const char* fragmentSource) const override;
		virtual Texture2D* createTexture2D0(const void* data, Texture::TextureProps props) const override;
		virtual FrameBuffer* createFrameBuffer0(const FrameBuffer::FrameBufferProps& frameBufferProps) const override;
	};
}
