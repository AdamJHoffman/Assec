#pragma once
#include "acpch.h"

namespace assec::graphics
{
	class Shader
	{
	public:
		virtual ~Shader() { TIME_FUNCTION; }
		virtual void cleanup() const = 0;
		unsigned int m_RendererID;
	protected:
		Shader(unsigned int ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const unsigned int genShader(Type& type) const = 0;
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() { TIME_FUNCTION; }
		virtual void bind() const = 0;
		virtual void cleanup() const = 0;
		virtual void loadInt(std::string name, int value) = 0;
		unsigned int m_RendererID;
	protected:
		ShaderProgram(unsigned int ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const unsigned int genShaderProgram() const = 0;
		virtual int getLocation(const std::string& name) = 0;
		std::unordered_map<std::string, int> m_LocationCache = std::unordered_map<std::string, int>();
	};
}
