#pragma once

#include "graphics/GraphicsContext.h"

#ifdef AC_DEBUG
#define GLClearError() while(glGetError() != GL_NO_ERROR)
#define GLCall(x)   GLClearError();\
                    x;\
                    {\
                    uint32_t error = glGetError();\
					AC_CORE_ASSERT(!error, ("Assertion failed: [OPENGL ERROR {0}] in function \"{1}\" on line {2} in file \"{3}\"", error, #x, __LINE__, __FILE__))\
					}
#else
#define GLCall(x) x
#endif // AC_DEBUG

namespace assec::graphics
{
	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext();
		virtual ~OpenGLGraphicsContext();
		virtual const void init() const override;
		virtual void setActiveTexture(const uint32_t& texture) const override;
		virtual void setClearColor(const glm::vec4& color) const override;
		virtual void enable(const Type& type) const override;
		virtual void setDepthFunction(const Type& type) const override;
		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const override;
		virtual ref<IndexBuffer> createIndexBuffer(const void* indices, const size_t& size, const int& usage) const override;
		virtual ref<VertexArray> createVertexArray(const VertexArray::VertexArrayProps& vertexArrayData) const override;
		virtual ref<VertexArray> createVertexArray(const Type& usage, const size_t& size) const override;
		virtual ref<Shader> createShader(const std::string& source, const Type& type) const override;
		virtual ref<ShaderProgram> createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) const override;
		virtual ref<ShaderProgram> createShaderProgram(const std::string& source) const override;
		virtual ref<Texture2D> createTexture2D(const uint32_t& width, const uint32_t& height, const graphics::Texture::TextureProps& props) const override;
		virtual ref<Texture2D> createTexture2D(const std::string& path, const graphics::Texture::TextureProps& props) const override;
		virtual ref<FrameBuffer> createFrameBuffer(const FrameBuffer::FrameBufferProps& frameBufferProps) const override;
	};

	uint32_t toOpenGLType(const Type&);
	Type fromOpenGLType(const uint32_t&);
} // assec::graphics
