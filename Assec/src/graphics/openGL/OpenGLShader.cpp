#include "acpch.h"
#include "OpenGLShader.h"

namespace assec::graphics
{
	OpenGLShader::OpenGLShader(const char* source, Type type) : Shader::Shader(this->genShader(type))
	{
		TIME_FUNCTION;
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
	OpenGLShader::~OpenGLShader() { TIME_FUNCTION; }
	void OpenGLShader::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteShader(this->m_RendererID));
	}
	const unsigned int OpenGLShader::genShader(Type& type) const
	{
		TIME_FUNCTION;
		GLCall(unsigned int ID = glCreateShader(toOpenGLType(type)));
		return ID;
	}
	OpenGLShaderProgram::OpenGLShaderProgram(const char* vertexSource, const char* fragmentSource) : ShaderProgram::ShaderProgram(this->genShaderProgram())
	{
		TIME_FUNCTION;
		int success;
		char infoLog[512];
		assec::scope<Shader> vertexShader = std::make_unique<OpenGLShader>(vertexSource, Type::VERTEX_SHADER);
		assec::scope<Shader> fragmentShader = std::make_unique<OpenGLShader>(fragmentSource, Type::FRAGMENT_SHADER);
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
	OpenGLShaderProgram::~OpenGLShaderProgram() { TIME_FUNCTION; }
	void OpenGLShaderProgram::cleanup() const
	{
		TIME_FUNCTION;
		GLCall(glDeleteProgram(this->m_RendererID));
	}
	void OpenGLShaderProgram::bind() const
	{
		TIME_FUNCTION;
		GLCall(glUseProgram(this->m_RendererID));
	}
	void OpenGLShaderProgram::loadInt(std::string name, int value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniform1i(this->getLocation(name), value));
	}
	void OpenGLShaderProgram::loadIntArray(std::string name, size_t size, int* value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniform1iv(this->getLocation(name), size, value));
	}
	void OpenGLShaderProgram::loadVec4(std::string name, glm::vec4 value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniform4fv(this->getLocation(name), 1, glm::value_ptr(value)));
	}
	void OpenGLShaderProgram::loadMat4(std::string name, glm::mat4 value)
	{
		TIME_FUNCTION;
		this->bind();
		GLCall(glUniformMatrix4fv(this->getLocation(name), 1, false, glm::value_ptr(value)));
	}
	const unsigned int OpenGLShaderProgram::genShaderProgram() const
	{
		TIME_FUNCTION;
		GLCall(unsigned int ID = glCreateProgram());
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
}
