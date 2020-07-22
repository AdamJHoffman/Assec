#pragma once
#include "acpch.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		virtual void loadIntArray(std::string name, size_t size, int* value) = 0;
		virtual void loadVec4(std::string name, glm::vec4 value) = 0;
		virtual void loadMat4(std::string name, glm::mat4 value) = 0;
		unsigned int m_RendererID;
	protected:
		ShaderProgram(unsigned int ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const unsigned int genShaderProgram() const = 0;
		virtual int getLocation(const std::string& name) = 0;
		std::unordered_map<std::string, int> m_LocationCache = std::unordered_map<std::string, int>();
	};
}
