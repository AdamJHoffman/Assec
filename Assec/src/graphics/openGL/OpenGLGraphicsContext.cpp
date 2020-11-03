#include "acpch.h"

#include "OpenGLGraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"

namespace assec::graphics
{
	OpenGLGraphicsContext::OpenGLGraphicsContext() : GraphicsContext::GraphicsContext() { TIME_FUNCTION; }
	OpenGLGraphicsContext::~OpenGLGraphicsContext() { TIME_FUNCTION; }
	const void OpenGLGraphicsContext::init() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Assertion failed: {0}", "failed to initialize OpenGL");
		int texture_units;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units));
		this->m_ContextData = { (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER),
			(const char*)glGetString(GL_VERSION), texture_units };
		AC_CORE_INFO("successfully initialized OpenGL: ");
		AC_CORE_INFO("	Vendor: {0}", this->m_ContextData.m_Vendor);
		AC_CORE_INFO("	Renderer: {0}", this->m_ContextData.m_Renderer);
		AC_CORE_INFO("	Version: {0}", this->m_ContextData.m_Version);
	}
	void OpenGLGraphicsContext::setActiveTexture(const uint32_t& texture) const
	{
		TIME_FUNCTION;
		GLCall(glActiveTexture(GL_TEXTURE0 + texture));
	}
	void OpenGLGraphicsContext::setClearColor(const glm::vec4& color) const
	{
		TIME_FUNCTION;
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
	}
	void OpenGLGraphicsContext::enable(const Type& type) const
	{
		TIME_FUNCTION;
		GLCall(glEnable(toOpenGLType(type)));
	}
	void OpenGLGraphicsContext::setDepthFunction(const Type& type) const
	{
		TIME_FUNCTION;
		GLCall(glDepthFunc(toOpenGLType(type)));
	}
	ref<VertexBuffer> OpenGLGraphicsContext::createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexBuffer>(vertices, size, usage);
	}
	ref<IndexBuffer> OpenGLGraphicsContext::createIndexBuffer(const void* indices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLIndexBuffer>(indices, size, usage);
	}
	ref<VertexArray> OpenGLGraphicsContext::createVertexArray(const VertexArray::VertexArrayProps& vertexArrayData) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexArray>(vertexArrayData);
	}
	ref<VertexArray> OpenGLGraphicsContext::createVertexArray(const Type& usage, const size_t& size) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexArray>(toOpenGLType(usage), size);
	}
	ref<Shader> OpenGLGraphicsContext::createShader(const std::string& source, const Type& type) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLShader>(source, type);
	}
	ref<ShaderProgram> OpenGLGraphicsContext::createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLShaderProgram>(vertexSource, fragmentSource);
	}
	ref<ShaderProgram> OpenGLGraphicsContext::createShaderProgram(const std::string& source) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLShaderProgram>(source);
	}
	ref<Texture2D> OpenGLGraphicsContext::createTexture2D(const void* data, const Texture::TextureProps& props) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLTexture2D>(data, props);
	}
	ref<FrameBuffer> OpenGLGraphicsContext::createFrameBuffer(const FrameBuffer::FrameBufferProps& frameBufferProps) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLFrameBuffer>(frameBufferProps);
	}
	uint32_t toOpenGLType(const Type& type)
	{
		TIME_FUNCTION;
		switch (type)
		{
		case Type::FLOAT:
			return GL_FLOAT;
			break;
		case Type::UNSIGNED_INT:
			return GL_UNSIGNED_INT;
			break;
		case Type::UNSIGNED_BYTE:
			return GL_UNSIGNED_BYTE;
			break;
		case Type::UNSIGNED_INT_24_8:
			return GL_UNSIGNED_INT_24_8;
			break;
		case Type::VERTEX_SHADER:
			return GL_VERTEX_SHADER;
			break;
		case Type::FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;
			break;
		case Type::DEPTH_TEST:
			return GL_DEPTH_TEST;
			break;
		case Type::LESS:
			return GL_LESS;
			break;
		case Type::STATIC_DRAW:
			return GL_STATIC_DRAW;
			break;
		case Type::DYNAMIC_DRAW:
			return GL_DYNAMIC_DRAW;
			break;
		case Type::REPEAT:
			return GL_REPEAT;
			break;
		case Type::MIRRORED_REPEAT:
			return GL_MIRRORED_REPEAT;
			break;
		case Type::CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;
			break;
		case Type::CLAMP_TO_BORDER:
			return GL_CLAMP_TO_BORDER;
			break;
		case Type::LINEAR:
			return GL_LINEAR;
			break;
		case Type::NEAREST:
			return GL_NEAREST;
			break;
		case Type::NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;
			break;
		case Type::LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;
			break;
		case Type::NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;
			break;
		case Type::LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
			break;
		case Type::RGB:
			return GL_RGB;
			break;
		case Type::RGBA:
			return GL_RGBA;
			break;
		case Type::RGBA8:
			return GL_RGBA8;
			break;
		case Type::DEPTH24_STENCIL8:
			return GL_DEPTH24_STENCIL8;
			break;
		case Type::DEPTH_STENCIL:
			return GL_DEPTH_STENCIL;
			break;
		case Type::COLOR_ATTACHMENT_0:
			return GL_COLOR_ATTACHMENT0;
			break;
		case Type::DEPTH_STENCIL_ATTACHMENT:
			return GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		default:
			return NULL;
			break;
		}
	}
} // assec::graphics
