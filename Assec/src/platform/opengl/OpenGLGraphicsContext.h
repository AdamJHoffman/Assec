#pragma once

#include <glad/glad.h>

#include "graphics/GraphicsContext.h"

#ifdef AC_DEBUG

#define GLCall(x)   while(glGetError() != GL_NO_ERROR);\
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
		virtual void init() override;
		virtual void cleanup() override;

		virtual void clear(CONST_REF(std::vector<BufferBitMask>)) const override;
		virtual void clearColor(CONST_REF(glm::vec4)) const override;
		virtual void clearDepth(CONST_REF(float)) const override;
		virtual void clearStencil(CONST_REF(int)) const override;
		virtual void finish(void) const override;
		virtual void flush(void) const override;
		virtual void readBuffer(CONST_REF(DrawBuffer)) const override;
		virtual std::vector<unsigned char> readPixels(const glm::vec<2, int>&,
			const glm::vec<2, int>&, CONST_REF(InternalFormat)) const override;

		virtual void setActiveTexture(const uint32_t& texture) const override;
		virtual void enable(const Type& type) const override;
		virtual void setDepthFunction(const Type& type) const override;
		virtual void setBlendFunction(const Type& sfactor, const Type& dfactor) const override;
		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const override;
		virtual ref<IndexBuffer> createIndexBuffer(CONST_REF(std::vector<uint32_t>) data, const int& usage) const override;
		virtual ref<VertexArray> createVertexArray(const VertexArray::VertexArrayProps& vertexArrayData) const override;
		virtual ref<VertexArray> createVertexArray(const Usage& usage, const size_t& size) const override;
		virtual ref<Shader> createShader(const std::string& source, const Type& type) const override;
		virtual ref<ShaderProgram> createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) const override;
		virtual ref<ShaderProgram> createShaderProgram(const std::string& source) const override;
		virtual ref<Texture2D> createTexture2D(const uint32_t& width, const uint32_t& height, const graphics::Texture::TextureProps& props) const override;
		virtual ref<Texture2D> createTexture2D(const std::string& path, const graphics::Texture::TextureProps& props) const override;
		virtual ref<Framebuffer> createFrameBuffer(const FramebufferProps& frameBufferProps) const override;
	};

	uint32_t toOpenGLType(const Type&);
	uint32_t toOpenGLType(const Usage&);
	uint32_t toOpenGLType(const Access&);
	uint32_t toOpenGLType(const BufferTarget&);
	uint32_t toOpenGLType(const DataType&);
	uint32_t toOpenGLType(const DrawBuffer&);
	uint32_t toOpenGLType(const FrameBufferAttachment&);
	uint32_t toOpenGLType(const Format&);
	uint32_t toOpenGLType(const InternalFormat&);
	uint32_t toOpenGLType(const BufferBitMask&);
	uint32_t toOpenGLType(const BufferMask&);
	uint32_t toOpenGLType(const BufferStorageFlag&);

	Type fromOpenGLType(const uint32_t&);
	Format formatFromOpenGLType(const uint32_t&);

	Format determineFormat(CONST_REF(InternalFormat));
	DataType determineDataType(CONST_REF(InternalFormat));
} // assec::graphics
