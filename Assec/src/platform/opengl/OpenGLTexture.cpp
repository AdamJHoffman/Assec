#include "acpch.h"

#include <stb_image.h>

#include "OpenGLTexture.h"
#include "OpenGLGraphicsContext.h"

namespace assec::graphics
{
	OpenGLTexture2D::OpenGLTexture2D(const uint32_t& width, const uint32_t& height, const TextureProps& props) : Texture2D::Texture2D(this->genTexture(), width, height, std::string(), props)
	{
		TIME_FUNCTION;

		this->bind();
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, toOpenGLType(this->m_Props.internalFormat), this->m_Width, this->m_Height, 0, toOpenGLType(this->m_Props.dataFormat), toOpenGLType(this->m_Props.dataType), nullptr));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toOpenGLType(this->m_Props.wrapType)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toOpenGLType(this->m_Props.wrapType)));

		GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->m_Props.borderColor)));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGLType(this->m_Props.minFilterType)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGLType(this->m_Props.magFilterType)));

		if (this->m_Props.genMipMaps)
		{
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}

		if (this->m_Props.genAnisotropicMaps)
		{
			float aniso = 0.0f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		}
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const TextureProps& props) : Texture2D::Texture2D(this->genTexture(), 0, 0, path, props)
	{
		TIME_FUNCTION;

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		int desired_channels = 0;
		switch (this->m_Props.dataFormat)
		{
		case Type::RED:
			desired_channels = STBI_grey;
			break;
		case Type::RG:
			desired_channels = STBI_grey_alpha;
			break;
		case Type::RGB:
			desired_channels = STBI_rgb;
			break;
		case Type::RGBA:
			desired_channels = STBI_rgb_alpha;
			break;
		}

		stbi_uc* data = nullptr;
		{
			data = stbi_load(path.c_str(), &width, &height, &channels, desired_channels);
		}
		if (stbi_failure_reason())
		{
			AC_CORE_WARNING(stbi_failure_reason());
		}
		AC_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		AC_CORE_ASSERT((this->m_Props.internalFormat != Type::NONE && this->m_Props.dataFormat != Type::NONE), "Format not supported!");

		GLCall(glTextureStorage2D(this->m_RendererID, 1, toOpenGLType(this->m_Props.internalFormat), this->m_Width, this->m_Height));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toOpenGLType(this->m_Props.wrapType)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toOpenGLType(this->m_Props.wrapType)));

		GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->m_Props.borderColor)));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGLType(this->m_Props.minFilterType)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGLType(this->m_Props.magFilterType)));

		if (this->m_Props.genMipMaps)
		{
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}

		if (this->m_Props.genAnisotropicMaps)
		{
			float aniso = 0.0f;
			GLCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso));
			GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso));
		}

		this->setData(data, this->m_Width * this->m_Height * desired_channels);

		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D() 
	{ 
		TIME_FUNCTION; 
		GLCall(glDeleteTextures(1, &this->m_RendererID));
	}
	void OpenGLTexture2D::bind() const
	{
		TIME_FUNCTION;
		GLCall(glBindTexture(GL_TEXTURE_2D, this->m_RendererID));
	}
	void OpenGLTexture2D::setData(const void* data, const uint32_t& size) const
	{
		this->bind();
		uint32_t channels = 0;
		if (this->m_Props.dataFormat == fromOpenGLType(GL_RED))
		{
			channels = 1;
		}
		else if (this->m_Props.dataFormat == fromOpenGLType(GL_RG))
		{
			channels = 2;
		}
		else if (this->m_Props.dataFormat == fromOpenGLType(GL_RGB))
		{
			channels = 3;
		}
		else if (this->m_Props.dataFormat == fromOpenGLType(GL_RGBA))
		{
			channels = 4;
		}
		AC_CORE_ASSERT(size == m_Width * m_Height * channels, "Data must be entire texture!");
		GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, toOpenGLType(this->m_Props.dataFormat), toOpenGLType(this->m_Props.dataType), data));
	}
	void* OpenGLTexture2D::getData() const
	{
		this->bind();
		uint32_t channels = 0;
		if (this->m_Props.dataFormat == fromOpenGLType(GL_RED))
		{
			channels = 1;
		}
		else if (this->m_Props.dataFormat == fromOpenGLType(GL_RG))
		{
			channels = 2;
		}
		else if (this->m_Props.dataFormat == fromOpenGLType(GL_RGB))
		{
			channels = 3;
		}
		else if (this->m_Props.dataFormat == fromOpenGLType(GL_RGBA) || this->m_Props.dataFormat == fromOpenGLType(GL_RED_INTEGER))
		{
			channels = 4;
		}
		uint32_t size = this->m_Width * this->m_Height * channels;
		unsigned char* result = new unsigned char[size];
		glGetTextureImage(this->m_RendererID, 0, toOpenGLType(this->m_Props.dataFormat), toOpenGLType(this->m_Props.dataType), size, result);
		return result;
	}
	void OpenGLTexture2D::clear() const 
	{
		GLCall(glClearTexImage(this->m_RendererID, 0, toOpenGLType(this->m_Props.dataFormat), toOpenGLType(this->m_Props.dataType), 0));
	}

	const uint32_t OpenGLTexture2D::genTexture() const
	{
		TIME_FUNCTION;
		uint32_t ID;
		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &ID));
		return ID;
	}
} // assec::graphics
