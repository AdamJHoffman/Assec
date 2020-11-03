#include "acpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

#include "OpenGLGraphicsContext.h"

namespace assec::graphics
{
	OpenGLShader::OpenGLShader(const std::string& source, const Type& type) : Shader::Shader(this->genShader(type))
	{
		TIME_FUNCTION;
		const GLchar* sourceCStr = source.c_str();
		GLCall(glShaderSource(this->m_RendererID, 1, &sourceCStr, NULL));
		GLCall(glCompileShader(this->m_RendererID));
		int success;
		GLCall(glGetShaderiv(this->m_RendererID, GL_COMPILE_STATUS, &success));
		if (!success)
		{
			char infoLog[512];
			GLCall(glGetShaderInfoLog(this->m_RendererID, 512, NULL, infoLog));
			AC_CORE_ASSERT(false, "Failed to compile shader: \n{0}", infoLog);
		};
	}
	OpenGLShader::~OpenGLShader() 
	{ 
		TIME_FUNCTION; 
		GLCall(glDeleteShader(this->m_RendererID));
	}
	const uint32_t OpenGLShader::genShader(const Type& type) const
	{
		TIME_FUNCTION;
		GLCall(uint32_t ID = glCreateShader(toOpenGLType(type)));
		return ID;
	}
	OpenGLShaderProgram::OpenGLShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) : ShaderProgram::ShaderProgram(this->genShaderProgram())
	{
		TIME_FUNCTION;
		scope<Shader> vertexShader = std::make_unique<OpenGLShader>(vertexSource, Type::VERTEX_SHADER);
		scope<Shader> fragmentShader = std::make_unique<OpenGLShader>(fragmentSource, Type::FRAGMENT_SHADER);
		GLCall(glAttachShader(this->m_RendererID, vertexShader->m_RendererID));
		GLCall(glAttachShader(this->m_RendererID, fragmentShader->m_RendererID));
		glLinkProgram(this->m_RendererID);
		int success;
		glGetProgramiv(this->m_RendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(this->m_RendererID, 512, NULL, infoLog);
			AC_CORE_ASSERT(false, "Shaderprogram compilation failed: \n{0}", infoLog);
		}
	}
	OpenGLShaderProgram::OpenGLShaderProgram(const std::string& source) : OpenGLShaderProgram::OpenGLShaderProgram(this->findVertexSubString(source), this->findFragmentSubString(source)) { TIME_FUNCTION; }
	OpenGLShaderProgram::~OpenGLShaderProgram() 
	{ 
		TIME_FUNCTION; 
		GLCall(glDeleteProgram(this->m_RendererID));
	}
	void OpenGLShaderProgram::bind() const
	{
		TIME_FUNCTION;
		GLCall(glUseProgram(this->m_RendererID));
	}
	void OpenGLShaderProgram::loadInt(const std::string& name, const int& value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniform1i(this->getLocation(name), value));
	}
	void OpenGLShaderProgram::loadIntArray(const std::string& name, const size_t& size, const int* value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniform1iv(this->getLocation(name), static_cast<GLsizei>(size), value));
	}
	void OpenGLShaderProgram::loadVec4(const std::string& name, const glm::vec4& value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniform4fv(this->getLocation(name), 1, glm::value_ptr(value)));
	}
	void OpenGLShaderProgram::loadMat4(const std::string& name, const glm::mat4& value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniformMatrix4fv(this->getLocation(name), 1, false, glm::value_ptr(value)));
	}
	const uint32_t OpenGLShaderProgram::genShaderProgram() const
	{
		TIME_FUNCTION;
		GLCall(uint32_t ID = glCreateProgram());
		return ID;
	}
	int OpenGLShaderProgram::getLocation(const std::string& name)
	{
		TIME_FUNCTION;
		if (this->m_LocationCache.find(name) == this->m_LocationCache.end())
		{
			GLCall(this->m_LocationCache[name] = glGetUniformLocation(this->m_RendererID, name.c_str()));
		}
		return this->m_LocationCache[name];
	}
	const std::string OpenGLShaderProgram::findVertexSubString(const std::string& source) const
	{
		size_t pos;
		if ((pos = source.find("fragment:")) != std::string::npos)
		{
			return source.substr(11, pos - 12);
		}
		return std::string();
	}
	const std::string OpenGLShaderProgram::findFragmentSubString(const std::string& source) const
	{
		size_t pos;
		if ((pos = source.find("fragment:")) != std::string::npos)
		{
			return source.substr(pos + 10, source.length() - (pos + 11));
		}
		return std::string();
	}
} // assec::graphics
