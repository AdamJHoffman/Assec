#pragma once

#include <glad/glad.h>

#include "graphics/GraphicsContext.h"

#ifdef AC_DEBUG

void glCheckError_(CONST_REF(std::string) file, int line, CONST_REF(std::string) function);
#define GLClearError() while(glGetError() != GL_NO_ERROR)
#define GLCall(x)   GLClearError();\
                    x;\
					{\
						uint32_t errorCode = glGetError();\
						std::string error;\
						switch (errorCode)\
						{\
							case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break;\
							case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break;\
							case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break;\
							case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break;\
							case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break;\
							case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break;\
							case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;\
						}\
						std::string message = std::string("[ ") + error + std::string(" ] in function \"") + std::string(#x) + std::string("\" on line ") + std::to_string(__LINE__) + std::string(" in file \"") + std::string(__FILE__) + std::string("\"");\
						AC_CORE_ASSERT(!errorCode, (message))\
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
		virtual void setBlendFunction(const Type& sfactor, const Type& dfactor) const override;
		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const override;
		virtual ref<IndexBuffer> createIndexBuffer(CONST_REF(std::vector<uint32_t>) data, const int& usage) const override;
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
	uint32_t toOpenGLType(const Usage&);
	uint32_t toOpenGLType(const Access&);
	uint32_t toOpenGLType(const BufferTarget&);

	Type fromOpenGLType(const uint32_t&);
} // assec::graphics
