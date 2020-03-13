#pragma once
#include "acpch.h"

namespace assec::graphics
{
	class Shader
	{
	public:
		virtual ~Shader() {}
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
	protected:
		Shader(unsigned int ID) : m_RendererID(ID) {}
		virtual const unsigned int genShader(DataType& type) const = 0;
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() {}
		virtual void bind() const = 0;
		unsigned int m_RendererID;
	protected:
		ShaderProgram(unsigned int ID) : m_RendererID(ID) {}
		virtual const unsigned int genShaderProgram() const = 0;
	};
}
