#pragma once
#include "graphics/Shader.h"
#include "core/OpenGLConfig.h"

namespace assec::graphics
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* source, DataType type);
		~OpenGLShader();
		virtual void cleanup() const override;
	protected:
		virtual const unsigned int genShader(DataType& type) const override;
	};

	class OpenGLShaderProgram : public ShaderProgram
	{
	public:
		OpenGLShaderProgram(const char* vertexSource, const char* fragmentSource);
		virtual ~OpenGLShaderProgram();
		virtual void bind() const override;
	protected:
		virtual const unsigned int genShaderProgram() const override;
	};
}
