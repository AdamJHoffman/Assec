#include "acpch.h"

#include "OpenGLGraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLFramebuffer.h"

namespace assec::graphics
{
	OpenGLGraphicsContext::OpenGLGraphicsContext() : GraphicsContext::GraphicsContext() { TIME_FUNCTION; }
	OpenGLGraphicsContext::~OpenGLGraphicsContext() { TIME_FUNCTION; }
	void OpenGLGraphicsContext::init()
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Assertion failed: failed to initialize OpenGL");
		int texture_units;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units));
		this->m_ContextData = { (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER),
			(const char*)glGetString(GL_VERSION), texture_units };
		AC_CORE_INFO("successfully initialized OpenGL: ");
		AC_CORE_INFO("	Vendor: {0}", this->m_ContextData.m_Vendor);
		AC_CORE_INFO("	Renderer: {0}", this->m_ContextData.m_Renderer);
		AC_CORE_INFO("	Version: {0}", this->m_ContextData.m_Version);
	}

	void OpenGLGraphicsContext::cleanup() {}

	void OpenGLGraphicsContext::clear(CONST_REF(std::vector<BufferBitMask>) buffermask) const
	{
		TIME_FUNCTION;
		GLenum mask = 0;
		for (auto& bit : buffermask)
		{
			mask |= toOpenGLType(bit);
		}
		GLCall(glClear(mask));
	}
	void OpenGLGraphicsContext::clearColor(CONST_REF(glm::vec4) color) const
	{
		TIME_FUNCTION;
		GLCall(glClearColor(color.r, color.g, color.b, color.a));
	}
	void OpenGLGraphicsContext::clearDepth(CONST_REF(float) depth) const
	{
		TIME_FUNCTION;
		GLCall(glClearDepthf(depth));
	}
	void OpenGLGraphicsContext::clearStencil(CONST_REF(int) stencil) const
	{
		TIME_FUNCTION;
		GLCall(glClearStencil(stencil));
	}
	void OpenGLGraphicsContext::finish(void) const
	{
		TIME_FUNCTION;
		GLCall(glFinish());
	}
	void OpenGLGraphicsContext::flush(void) const
	{
		TIME_FUNCTION;
		GLCall(glFlush());
	}
	void OpenGLGraphicsContext::readBuffer(CONST_REF(DrawBuffer) buffer) const
	{
		TIME_FUNCTION;
		GLCall(glReadBuffer(toOpenGLType(buffer)));
	}
	std::vector<unsigned char> OpenGLGraphicsContext::readPixels(const glm::vec<2, int>& pos,
		const glm::vec<2, int>& size, CONST_REF(InternalFormat) internalFormat) const
	{
		TIME_FUNCTION;
		std::vector<unsigned char> result = std::vector<unsigned char>(determineTotalSize(internalFormat) * size.x * size.y);
		GLCall(glReadPixels(pos.x, pos.y, size.x, size.y, toOpenGLType(determineFormat(internalFormat)), 
			toOpenGLType(determineDataType(internalFormat)), &result[0]));
		return result;
	}

	void OpenGLGraphicsContext::setActiveTexture(const uint32_t& texture) const
	{
		TIME_FUNCTION;
		GLCall(glActiveTexture(GL_TEXTURE0 + texture));
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
	void OpenGLGraphicsContext::setBlendFunction(const Type& sfactor, const Type& dfactor) const
	{
		TIME_FUNCTION;
		GLCall(glBlendFunc(toOpenGLType(sfactor), toOpenGLType(dfactor)));
	}
	ref<VertexBuffer> OpenGLGraphicsContext::createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const
	{
		TIME_FUNCTION;
		return nullptr;
	}
	ref<IndexBuffer> OpenGLGraphicsContext::createIndexBuffer(CONST_REF(std::vector<uint32_t>) data, const int& usage) const
	{
		TIME_FUNCTION;
		return nullptr;
	}
	ref<VertexArray> OpenGLGraphicsContext::createVertexArray(const VertexArray::VertexArrayProps& vertexArrayData) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLVertexArray>(vertexArrayData);
	}
	ref<VertexArray> OpenGLGraphicsContext::createVertexArray(const Usage& usage, const size_t& size) const
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
	ref<Texture2D> OpenGLGraphicsContext::createTexture2D(const uint32_t& width, const uint32_t& height, const graphics::Texture::TextureProps& props) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLTexture2D>(width, height, props);
	}
	ref<Texture2D> OpenGLGraphicsContext::createTexture2D(const std::string& path, const graphics::Texture::TextureProps& props) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLTexture2D>(path, props);
	}
	ref<Framebuffer> OpenGLGraphicsContext::createFrameBuffer(const FramebufferProps& frameBufferProps) const
	{
		TIME_FUNCTION;
		return std::make_shared<OpenGLFramebuffer>(frameBufferProps);
	}
	uint32_t toOpenGLType(const Type& type)
	{
		TIME_FUNCTION;
		switch (type)
		{
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
		case Type::BLEND:
			return GL_BLEND;
			break;
		case Type::SRC_ALPHA:
			return GL_SRC_ALPHA;
			break;
		case Type::ONE_MINUS_SRC_ALPHA:
			return GL_ONE_MINUS_SRC_ALPHA;
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
		case Type::RED:
			return GL_RED;
			break;
		case Type::RED_INTEGER:
			return GL_RED_INTEGER;
			break;
		case Type::R8:
			return GL_R8;
			break;
		case Type::R32UI:
			return GL_R32UI;
		case Type::R32I:
			return GL_R32I;
			break;
		case Type::RG:
			return GL_RG;
			break;
		case Type::RG8:
			return GL_RG8;
			break;
		case Type::RGB:
			return GL_RGB;
			break;
		case Type::RGB8:
			return GL_RGB8;
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
		case Type::COLOR_ATTACHMENT0:
			return GL_COLOR_ATTACHMENT0;
			break;
		case Type::COLOR_ATTACHMENT1:
			return GL_COLOR_ATTACHMENT1;
			break;
		case Type::DEPTH_STENCIL_ATTACHMENT:
			return GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const DataType& type)
	{
		switch(type)
		{
		case DataType::BYTE:
			return GL_BYTE;
			break;
		case DataType::UNSIGNED_BYTE:
			return GL_UNSIGNED_BYTE;
			break;
		case DataType::UNSIGNED_BYTE_3_3_2:
			return GL_UNSIGNED_BYTE_3_3_2;
			break;
		case DataType::SHORT:
			return GL_SHORT;
			break;
		case DataType::UNSIGNED_SHORT:
			return GL_UNSIGNED_SHORT;
			break;
		case DataType::UNSIGNED_SHORT_5_5_5_1:
			return GL_UNSIGNED_SHORT_5_5_5_1;
			break;
		case DataType::INT:
			return GL_INT;
			break;
		case DataType::UNSIGNED_INT:
			return GL_UNSIGNED_INT;
			break;
		case DataType::UNSIGNED_INT_24_8:
			return GL_UNSIGNED_INT_24_8;
			break;
		case DataType::UNSIGNED_INT_10F_11F_11F_REV:
			return GL_UNSIGNED_INT_10F_11F_11F_REV;
			break;
		case DataType::UNSIGNED_INT_5_9_9_9_REV:
			return GL_UNSIGNED_INT_5_9_9_9_REV;
			break;
		case DataType::UNSIGNED_INT_10_10_10_2:
			return GL_UNSIGNED_INT_10_10_10_2;
			break;
		case DataType::FLOAT:
			return GL_FLOAT;
			break;
		case DataType::FLOAT_32_UNSIGNED_INT_24_8_REV:
			return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
			break;
		case DataType::DOUBLE:
			return GL_DOUBLE;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const Usage& usage)
	{
		switch (usage)
		{
		case Usage::STREAM_DRAW:
			return GL_STREAM_DRAW;
			break;
		case Usage::STATIC_DRAW:
			return GL_STATIC_DRAW;
			break;
		case Usage::DYNAMIC_DRAW:
			return GL_DYNAMIC_DRAW;
			break;
		case Usage::STREAM_READ:
			return GL_STREAM_READ;
			break;
		case Usage::STATIC_READ:
			return GL_STATIC_READ;
			break;
		case Usage::DYNAMIC_READ:
			return GL_DYNAMIC_READ;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const Access& access)
	{
		switch (access)
		{
		case Access::READ_ONLY:
			return GL_READ_ONLY;
			break;
		case Access::WRITE_ONLY:
			return GL_WRITE_ONLY;
			break;
		case Access::READ_WRITE:
			return GL_READ_WRITE;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const BufferTarget& target)
	{
		switch (target)
		{
		case BufferTarget::ARRAY_BUFFER:
			return GL_ARRAY_BUFFER;
			break;
		case BufferTarget::ELEMENT_ARRAY_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const DrawBuffer& buffer)
	{
		switch (buffer)
		{
			case DrawBuffer::NONE:
				return GL_NONE;
				break;
			case DrawBuffer::FRONT_LEFT:
				return GL_FRONT_LEFT;
				break;
			case DrawBuffer::FRONT_RIGHT:
				return GL_FRONT_RIGHT;
				break;
			case DrawBuffer::BACK_LEFT:
				return GL_BACK_LEFT;
				break;
			case DrawBuffer::BACK_RIGHT:
				return GL_BACK_RIGHT;
				break;
			case DrawBuffer::COLOR_ATTACHMENT0:
				return GL_COLOR_ATTACHMENT0;
				break;
			case DrawBuffer::COLOR_ATTACHMENT1:
				return GL_COLOR_ATTACHMENT1;
				break;
			case DrawBuffer::COLOR_ATTACHMENT2:
				return GL_COLOR_ATTACHMENT2;
				break;
			case DrawBuffer::COLOR_ATTACHMENT3:
				return GL_COLOR_ATTACHMENT3;
				break;
			case DrawBuffer::COLOR_ATTACHMENT4:
				return GL_COLOR_ATTACHMENT4;
				break;
			case DrawBuffer::COLOR_ATTACHMENT5:
				return GL_COLOR_ATTACHMENT5;
				break;
			case DrawBuffer::COLOR_ATTACHMENT6:
				return GL_COLOR_ATTACHMENT6;
				break;
			case DrawBuffer::COLOR_ATTACHMENT7:
				return GL_COLOR_ATTACHMENT7;
				break;
			case DrawBuffer::COLOR_ATTACHMENT8:
				return GL_COLOR_ATTACHMENT8;
				break;
			case DrawBuffer::COLOR_ATTACHMENT9:
				return GL_COLOR_ATTACHMENT9;
				break;
			case DrawBuffer::COLOR_ATTACHMENT10:
				return GL_COLOR_ATTACHMENT10;
				break;
			case DrawBuffer::COLOR_ATTACHMENT11:
				return GL_COLOR_ATTACHMENT11;
				break;
			case DrawBuffer::COLOR_ATTACHMENT12:
				return GL_COLOR_ATTACHMENT12;
				break;
			case DrawBuffer::COLOR_ATTACHMENT13:
				return GL_COLOR_ATTACHMENT13;
				break;
			case DrawBuffer::COLOR_ATTACHMENT14:
				return GL_COLOR_ATTACHMENT14;
				break;
			case DrawBuffer::COLOR_ATTACHMENT15:
				return GL_COLOR_ATTACHMENT15;
				break;
			case DrawBuffer::COLOR_ATTACHMENT16:
				return GL_COLOR_ATTACHMENT16;
				break;
			case DrawBuffer::COLOR_ATTACHMENT17:
				return GL_COLOR_ATTACHMENT17;
				break;
			case DrawBuffer::COLOR_ATTACHMENT18:
				return GL_COLOR_ATTACHMENT18;
				break;
			case DrawBuffer::COLOR_ATTACHMENT19:
				return GL_COLOR_ATTACHMENT19;
				break;
			case DrawBuffer::COLOR_ATTACHMENT20:
				return GL_COLOR_ATTACHMENT20;
				break;
			case DrawBuffer::COLOR_ATTACHMENT21:
				return GL_COLOR_ATTACHMENT21;
				break;
			case DrawBuffer::COLOR_ATTACHMENT22:
				return GL_COLOR_ATTACHMENT22;
				break;
			case DrawBuffer::COLOR_ATTACHMENT23:
				return GL_COLOR_ATTACHMENT23;
				break;
			case DrawBuffer::COLOR_ATTACHMENT24:
				return GL_COLOR_ATTACHMENT24;
				break;
			case DrawBuffer::COLOR_ATTACHMENT25:
				return GL_COLOR_ATTACHMENT25;
				break;
			case DrawBuffer::COLOR_ATTACHMENT26:
				return GL_COLOR_ATTACHMENT26;
				break;
			case DrawBuffer::COLOR_ATTACHMENT27:
				return GL_COLOR_ATTACHMENT27;
				break;
			case DrawBuffer::COLOR_ATTACHMENT28:
				return GL_COLOR_ATTACHMENT28;
				break;
			case DrawBuffer::COLOR_ATTACHMENT29:
				return GL_COLOR_ATTACHMENT29;
				break;
			case DrawBuffer::COLOR_ATTACHMENT30:
				return GL_COLOR_ATTACHMENT30;
				break;
			case DrawBuffer::COLOR_ATTACHMENT31:
				return GL_COLOR_ATTACHMENT31;
				break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const FrameBufferAttachment& attachment)
	{
		switch (attachment)
		{
		case FrameBufferAttachment::COLOR_ATTACHMENT0:
			return GL_COLOR_ATTACHMENT0;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT1:
			return GL_COLOR_ATTACHMENT1;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT2:
			return GL_COLOR_ATTACHMENT2;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT3:
			return GL_COLOR_ATTACHMENT3;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT4:
			return GL_COLOR_ATTACHMENT4;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT5:
			return GL_COLOR_ATTACHMENT5;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT6:
			return GL_COLOR_ATTACHMENT6;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT7:
			return GL_COLOR_ATTACHMENT7;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT8:
			return GL_COLOR_ATTACHMENT8;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT9:
			return GL_COLOR_ATTACHMENT9;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT10:
			return GL_COLOR_ATTACHMENT10;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT11:
			return GL_COLOR_ATTACHMENT11;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT12:
			return GL_COLOR_ATTACHMENT12;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT13:
			return GL_COLOR_ATTACHMENT13;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT14:
			return GL_COLOR_ATTACHMENT14;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT15:
			return GL_COLOR_ATTACHMENT15;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT16:
			return GL_COLOR_ATTACHMENT16;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT17:
			return GL_COLOR_ATTACHMENT17;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT18:
			return GL_COLOR_ATTACHMENT18;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT19:
			return GL_COLOR_ATTACHMENT19;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT20:
			return GL_COLOR_ATTACHMENT20;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT21:
			return GL_COLOR_ATTACHMENT21;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT22:
			return GL_COLOR_ATTACHMENT22;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT23:
			return GL_COLOR_ATTACHMENT23;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT24:
			return GL_COLOR_ATTACHMENT24;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT25:
			return GL_COLOR_ATTACHMENT25;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT26:
			return GL_COLOR_ATTACHMENT26;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT27:
			return GL_COLOR_ATTACHMENT27;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT28:
			return GL_COLOR_ATTACHMENT28;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT29:
			return GL_COLOR_ATTACHMENT29;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT30:
			return GL_COLOR_ATTACHMENT30;
			break;
		case FrameBufferAttachment::COLOR_ATTACHMENT31:
			return GL_COLOR_ATTACHMENT31;
			break;
		case FrameBufferAttachment::DEPTH_ATTACHMENT:
			return GL_DEPTH_ATTACHMENT;
			break;
		case FrameBufferAttachment::STENCIL_ATTACHMENT:
			return GL_STENCIL_ATTACHMENT;
			break;
		case FrameBufferAttachment::DEPTH_STENCIL_ATTACHMENT:
			return GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const Format& format)
	{
		switch (format)
		{
		case Format::DEPTH_COMPONENT:
			return GL_DEPTH_COMPONENT;
			break;
		case Format::DEPTH_STENCIL:
			return GL_DEPTH_STENCIL;
			break;
		case Format::RED:
			return GL_RED;
			break;
		case Format::RED_INTEGER:
			return GL_RED_INTEGER;
			break;
		case Format::RG:
			return GL_RG;
			break;
		case Format::RG_INTEGER:
			return GL_RG_INTEGER;
			break;
		case Format::RGB:
			return GL_RGB;
			break;
		case Format::RGB_INTEGER:
			return GL_RGB_INTEGER;
			break;
		case Format::RGBA:
			return GL_RGBA;
			break;
		case Format::RGBA_INTEGER:
			return GL_RGBA_INTEGER;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	};

	uint32_t toOpenGLType(const InternalFormat& internalformat)
	{
		switch (internalformat)
		{
		case InternalFormat::DEPTH_COMPONENT16:
			return GL_DEPTH_COMPONENT16;
			break;
		case InternalFormat::DEPTH_COMPONENT24:
			return GL_DEPTH_COMPONENT24;
			break;
		case InternalFormat::DEPTH_COMPONENT32:
			return GL_DEPTH_COMPONENT32;
			break;
		case InternalFormat::DEPTH_COMPONENT32F:
			return GL_DEPTH_COMPONENT32F;
			break;
		case InternalFormat::DEPTH24_STENCIL8:
			return GL_DEPTH24_STENCIL8;
			break;
		case InternalFormat::DEPTH32F_STENCIL8:
			return GL_DEPTH32F_STENCIL8;
			break;
		case InternalFormat::R8:
			return GL_R8;
			break;
		case InternalFormat::R8_SNORM:
			return GL_R8_SNORM;
			break;
		case InternalFormat::R16:
			return GL_R16;
			break;
		case InternalFormat::R16_SNORM:
			return GL_R16_SNORM;
			break;
		case InternalFormat::RG8:
			return GL_RG8;
			break;
		case InternalFormat::RG8_SNORM:
			return GL_RG8_SNORM;
			break;
		case InternalFormat::RG16:
			return GL_RG16;
			break;
		case InternalFormat::RG16_SNORM:
			return GL_RG16_SNORM;
			break;
		case InternalFormat::R3_G3_B2:
			return GL_R3_G3_B2;
			break;
		case InternalFormat::RGB4:
			return GL_RGB4;
			break;
		case InternalFormat::RGB5:
			return GL_RGB5;
			break;
		case InternalFormat::RGB8:
			return GL_RGB8;
			break;
		case InternalFormat::RGB8_SNORM:
			return GL_RGB8_SNORM;
			break;
		case InternalFormat::RGB10:
			return GL_RGB10;
			break;
		case InternalFormat::RGB12:
			return GL_RGB12;
			break;
		case InternalFormat::RGB16:
			return GL_RGB16;
			break;
		case InternalFormat::RGB16_SNORM:
			return GL_RGB16_SNORM;
			break;
		case InternalFormat::RGBA2:
			return GL_RGBA2;
			break;
		case InternalFormat::RGBA4:
			return GL_RGBA4;
			break;
		case InternalFormat::RGB5_A1:
			return GL_RGB5_A1;
			break;
		case InternalFormat::RGBA8:
			return GL_RGBA8;
			break;
		case InternalFormat::RGBA8_SNORM:
			return GL_RGBA8_SNORM;
			break;
		case InternalFormat::RGB10_A2:
			return GL_RGB10_A2;
			break;
		case InternalFormat::RGBA12:
			return GL_RGBA12;
			break;
		case InternalFormat::RGBA16:
			return GL_RGBA16;
			break;
		case InternalFormat::RGBA16_SNORM:
			return GL_RGBA16_SNORM;
			break;
		case InternalFormat::SRGB8:
			return GL_SRGB8;
			break;
		case InternalFormat::SRGB8_ALPHA8:
			return GL_SRGB8_ALPHA8;
			break;
		case InternalFormat::R16F:
			return GL_R16F;
			break;
		case InternalFormat::RG16F:
			return GL_RG16F;
			break;
		case InternalFormat::RGB16F:
			return GL_RGB16F;
			break;
		case InternalFormat::RGBA16F:
			return GL_RGBA16F;
			break;
		case InternalFormat::R32F:
			return GL_R32F;
			break;
		case InternalFormat::RG32F:
			return GL_RG32F;
			break;
		case InternalFormat::RGB32F:
			return GL_RGB32F;
			break;
		case InternalFormat::RGBA32F:
			return GL_RGBA32F;
			break;
		case InternalFormat::R11F_G11F_B10F:
			return GL_R11F_G11F_B10F;
			break;
		case InternalFormat::RGB9_E5:
			return GL_RGB9_E5;
			break;
		case InternalFormat::R8I:
			return GL_R8I;
			break;
		case InternalFormat::R8UI:
			return GL_R8UI;
			break;
		case InternalFormat::R16I:
			return GL_R16I;
			break;
		case InternalFormat::R16UI:
			return GL_R16UI;
			break;
		case InternalFormat::R32I:
			return GL_R32I;
			break;
		case InternalFormat::R32UI:
			return GL_R32UI;
			break;
		case InternalFormat::RG8I:
			return GL_RG8I;
			break;
		case InternalFormat::RG8UI:
			return GL_RG8UI;
			break;
		case InternalFormat::RG16I:
			return GL_RG16I;
			break;
		case InternalFormat::RG16UI:
			return GL_RG16UI;
			break;
		case InternalFormat::RG32I:
			return GL_RG32I;
			break;
		case InternalFormat::RG32UI:
			return GL_RG32UI;
			break;
		case InternalFormat::RGB8I:
			return GL_RGB8I;
			break;
		case InternalFormat::RGB8UI:
			return GL_RGB8UI;
			break;
		case InternalFormat::RGB16I:
			return GL_RGB16I;
			break;
		case InternalFormat::RGB16UI:
			return GL_RGB16UI;
			break;
		case InternalFormat::RGB32I:
			return GL_RGB32I;
			break;
		case InternalFormat::RGB32UI:
			return GL_RGB32UI;
			break;
		case InternalFormat::RGBA8I:
			return GL_RGBA8I;
			break;
		case InternalFormat::RGBA8UI:
			return GL_RGBA8UI;
			break;
		case InternalFormat::RGBA16I:
			return GL_RGBA16I;
			break;
		case InternalFormat::RGBA16UI:
			return GL_RGBA16UI;
			break;
		case InternalFormat::RGBA32I:
			return GL_RGBA32I;
			break;
		case InternalFormat::RGBA32UI:
			return GL_RGBA32UI;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	};

	uint32_t toOpenGLType(const BufferBitMask& mask)
	{
		switch (mask)
		{
		case BufferBitMask::COLOR_BUFFER_BIT:
			return GL_COLOR_BUFFER_BIT;
			break;
		case BufferBitMask::DEPTH_BUFFER_BIT:
			return GL_DEPTH_BUFFER_BIT;
			break;
		case BufferBitMask::STENCIL_BUFFER_BIT:
			return GL_STENCIL_BUFFER_BIT;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const BufferMask& mask)
	{
		switch (mask)
		{
		case BufferMask::COLOR_BUFFER:
			return GL_COLOR;
			break;
		case BufferMask::DEPTH_BUFFER:
			return GL_DEPTH;
			break;
		case BufferMask::STENCIL_BUFFER:
			return GL_STENCIL;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return NULL;
			break;
		}
	}

	uint32_t toOpenGLType(const BufferStorageFlag& flag)
	{
		switch (flag)
		{
			case BufferStorageFlag::DYNAMIC_STORAGE_BIT:
				return GL_DYNAMIC_STORAGE_BIT;
				break;
			case BufferStorageFlag::MAP_READ_BIT:
				return GL_MAP_READ_BIT;
				break;
			case BufferStorageFlag::MAP_WRITE_BIT:
				return GL_MAP_WRITE_BIT;
				break;
			case BufferStorageFlag::MAP_PERSISTENT_BIT:
				return GL_MAP_PERSISTENT_BIT;
				break;
			case BufferStorageFlag::MAP_COHERENT_BIT:
				return GL_MAP_COHERENT_BIT;
				break;
			case BufferStorageFlag::CLIENT_STORAGE_BIT:
				return GL_CLIENT_STORAGE_BIT;
				break;
			default:
				AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
				return NULL;
				break;
		}
	}

	Type fromOpenGLType(const uint32_t& type)
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:
			return Type::VERTEX_SHADER;
			break;
		case GL_FRAGMENT_SHADER:
			return Type::FRAGMENT_SHADER;
			break;
		case GL_DEPTH_TEST:
			return Type::DEPTH_TEST;
			break;
		case GL_LESS:
			return Type::LESS;
			break;
		case GL_REPEAT:
			return Type::REPEAT;
			break;
		case GL_MIRRORED_REPEAT:
			return Type::MIRRORED_REPEAT;
			break;
		case GL_CLAMP_TO_EDGE:
			return Type::CLAMP_TO_EDGE;
			break;
		case GL_CLAMP_TO_BORDER:
			return Type::CLAMP_TO_BORDER;
			break;
		case GL_LINEAR:
			return Type::LINEAR;
			break;
		case GL_NEAREST:
			return Type::NEAREST;
			break;
		case GL_NEAREST_MIPMAP_NEAREST:
			return Type::NEAREST_MIPMAP_NEAREST;
			break;
		case GL_LINEAR_MIPMAP_NEAREST:
			return Type::LINEAR_MIPMAP_NEAREST;
			break;
		case GL_NEAREST_MIPMAP_LINEAR:
			return Type::NEAREST_MIPMAP_LINEAR;
			break;
		case GL_LINEAR_MIPMAP_LINEAR:
			return Type::LINEAR_MIPMAP_LINEAR;
			break;
		case GL_RED:
			return Type::RED;
			break;
		case GL_RED_INTEGER:
			return Type::RED_INTEGER;
			break;
		case GL_R8:
			return Type::R8;
			break;
		case GL_RG:
			return Type::RG;
			break;
		case GL_RG8:
			return Type::RG8;
			break;
		case GL_RGB:
			return Type::RGB;
			break;
		case GL_RGB8:
			return Type::RGB8;
			break;
		case GL_RGBA:
			return Type::RGBA;
			break;
		case GL_RGBA8:
			return Type::RGBA8;
			break;
		case GL_DEPTH24_STENCIL8:
			return Type::DEPTH24_STENCIL8;
			break;
		case GL_DEPTH_STENCIL:
			return Type::DEPTH_STENCIL;
			break;
		case GL_COLOR_ATTACHMENT0:
			return Type::COLOR_ATTACHMENT0;
			break;
		case GL_DEPTH_STENCIL_ATTACHMENT:
			return Type::DEPTH_STENCIL_ATTACHMENT;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion from opengl setup!");
			return Type::NONE;
			break;
		}
	}

	Format formatFromOpenGLType(const uint32_t& format)
	{
		switch (format)
		{
		case GL_DEPTH_COMPONENT:
			return Format::DEPTH_COMPONENT;
			break;
		case GL_DEPTH_STENCIL:
			return Format::DEPTH_STENCIL;
			break;
		case GL_RED:
			return Format::RED;
			break;
		case GL_RED_INTEGER:
			return Format::RED_INTEGER;
			break;
		case GL_RG:
			return Format::RG;
			break;
		case GL_RG_INTEGER:
			return Format::RG_INTEGER;
			break;
		case GL_RGB:
			return Format::RGB;
			break;
		case GL_RGB_INTEGER:
			return Format::RGB_INTEGER;
			break;
		case GL_RGBA:
			return Format::RGBA;
			break;
		case GL_RGBA_INTEGER:
			return Format::RGBA_INTEGER;
			break;
		default:
			AC_CORE_ASSERT(false, "no proper conversion to opengl set up!");
			return Format::RED;
			break;
		}
	}
} // assec::graphics
