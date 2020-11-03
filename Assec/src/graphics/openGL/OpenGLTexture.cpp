#include "acpch.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "OpenGLGraphicsContext.h"

namespace assec::graphics
{
	OpenGLTexture2D::OpenGLTexture2D(const void* data, const Texture::TextureProps& props) : Texture2D::Texture2D(this->genTexture(), props)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, toOpenGLType(this->m_Props.m_Internalformat), this->m_Props.m_Width, this->m_Props.m_Height, 0, toOpenGLType(this->m_Props.m_Format), toOpenGLType(this->m_Props.m_Type), data));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toOpenGLType(this->m_Props.m_WrapType)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toOpenGLType(this->m_Props.m_WrapType)));
		GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->m_Props.m_BorderColor)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGLType(this->m_Props.m_MinFilterType)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGLType(this->m_Props.m_MagFilterType)));
		if (this->m_Props.m_GenMipMaps)
		{
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		if (this->m_Props.m_GenAnisotropicMaps)
		{
			float aniso = 0.0f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		}
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
	const uint32_t OpenGLTexture2D::genTexture() const
	{
		TIME_FUNCTION;
		uint32_t ID;
		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &ID));
		return ID;
	}
} // assec::graphics
