#include "acpch.h"
#include "OpenGLShader.h"

namespace assec::graphics
{
	OpenGLShader::OpenGLShader(const char* source, DataType type) : Shader::Shader(this->genShader(type))
	{
		int success;
		char infoLog[512];
		GLCall(glShaderSource(this->m_RendererID, 1, &source, NULL));
		GLCall(glCompileShader(this->m_RendererID));
		GLCall(glGetShaderiv(this->m_RendererID, GL_COMPILE_STATUS, &success));
		if (!success)
		{
			GLCall(glGetShaderInfoLog(this->m_RendererID, 512, NULL, infoLog));
			AC_CORE_ASSERT(false, "Assertion failed: \n{0}", infoLog);
		};
	}
	OpenGLShader::~OpenGLShader() {}
	void OpenGLShader::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteShader(this->m_RendererID));
	}
	const unsigned int OpenGLShader::genShader(DataType& type) const
	{
		TIME_FUNCTION;
		GLCall(unsigned int ID = glCreateShader(toOpenGLType(type)));
		return ID;
	}
	OpenGLShaderProgram::OpenGLShaderProgram(const char* vertexSource, const char* fragmentSource) : ShaderProgram::ShaderProgram(this->genShaderProgram())
	{
		int success;
		char infoLog[512];
		assec::scope<Shader> vertexShader = std::make_unique<OpenGLShader>(vertexSource, DataType::VERTEX_SHADER);
		assec::scope<Shader> fragmentShader = std::make_unique<OpenGLShader>(fragmentSource, DataType::FRAGMENT_SHADER);
		GLCall(glAttachShader(this->m_RendererID, vertexShader->m_RendererID));
		GLCall(glAttachShader(this->m_RendererID, fragmentShader->m_RendererID));
		glLinkProgram(this->m_RendererID);
		glGetProgramiv(this->m_RendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->m_RendererID, 512, NULL, infoLog);
			AC_CORE_ASSERT(false, "Assertion failed: \n{0}", infoLog);
		}
		vertexShader->cleanup();
		fragmentShader->cleanup();
	}
	OpenGLShaderProgram::~OpenGLShaderProgram() {}
	void OpenGLShaderProgram::bind() const
	{
		TIME_FUNCTION;
		GLCall(glUseProgram(this->m_RendererID));
	}
	const unsigned int OpenGLShaderProgram::genShaderProgram() const
	{
		TIME_FUNCTION;
		GLCall(unsigned int ID = glCreateProgram());
		return ID;
	}
}
