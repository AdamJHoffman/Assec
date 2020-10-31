#pragma once

#include "graphics/Shader.h"

namespace assec::graphics
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& source, const Type& type);
		~OpenGLShader();
		virtual void cleanup() const override;
	protected:
		virtual const uint32_t genShader(const Type& type) const override;
	};

	class OpenGLShaderProgram : public ShaderProgram
	{
	public:
		OpenGLShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShaderProgram(const std::string& source);
		virtual ~OpenGLShaderProgram();
		virtual void cleanup() const override;
		virtual void loadInt(const std::string& name, const int& value) override;
		virtual void loadIntArray(const std::string& name, const size_t& size, const int* value) override;
		virtual void loadVec4(const std::string& name, const glm::vec4& value) override;
		virtual void loadMat4(const std::string& name, const glm::mat4& value) override;
		virtual void bind() const override;
	protected:
		virtual const uint32_t genShaderProgram() const override;
		virtual int getLocation(const std::string& name) override;
	};
} // assec::graphics
