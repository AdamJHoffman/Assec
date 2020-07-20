#pragma once
#include "graphics/Shader.h"
#include "core/OpenGLConfig.h"

namespace assec::graphics
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* source, Type type);
		~OpenGLShader();
		virtual void cleanup() const override;
	protected:
		virtual const unsigned int genShader(Type& type) const override;
	};

	class OpenGLShaderProgram : public ShaderProgram
	{
	public:
		OpenGLShaderProgram(const char* vertexSource, const char* fragmentSource);
		virtual ~OpenGLShaderProgram();
		virtual void cleanup() const override;
		virtual void loadInt(std::string name, int value) override;
		virtual void loadVec4(std::string name, glm::vec4 value) override;
		virtual void loadMat4(std::string name, glm::mat4 value) override;
		virtual void bind() const override;
	protected:
		virtual const unsigned int genShaderProgram() const override;
		virtual int getLocation(const std::string& name) override;
	};
}
