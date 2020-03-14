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
		virtual void setActiveTexture(unsigned int texture) const override;
		virtual const ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const override;
		virtual const ref<IndexBuffer> createIndexBuffer(const void* indices, const size_t& size, const int& usage) const override;
		virtual const ref<VertexArray> createVertexArray(const void* vertices, const size_t& verticesSize, const void* indices, const size_t& indicesSize, const int& usage, graphics::VertexBuffer::VertexBufferLayout& layout) const override;
		virtual const ref<Shader> createShader(const char* source, Type& type) const override;
		virtual const ref<ShaderProgram> createShaderProgram(const char* vertexSource, const char* fragmentSource) const override;
		virtual const ref<Texture2D> createTexture2D(unsigned int width, unsigned int height, const void* data, Texture::TextureProps props) const override;
	};
}
