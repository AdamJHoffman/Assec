#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Base.h"
#include "core/KeyCode.h"

namespace assec::graphics
{
	class Shader
	{
	public:
		virtual ~Shader() { TIME_FUNCTION; }
		uint32_t m_RendererID;
	protected:
		Shader(const uint32_t& ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const uint32_t genShader(const Type& type) const = 0;
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() { TIME_FUNCTION; }
		ShaderProgram(const ShaderProgram& other)
			: m_RendererID(other.m_RendererID), m_LocationCache(other.m_LocationCache) {}
		virtual void bind() const = 0;
		virtual void loadInt(const std::string& name, const int& value) = 0;
		virtual void loadIntArray(const std::string& name, const size_t& size, const int* value) = 0;
		virtual void loadVec4(const std::string& name, const glm::vec4& value) = 0;
		virtual void loadMat4(const std::string& name, const glm::mat4& value) = 0;
		uint32_t m_RendererID;
		bool operator==(const ShaderProgram& other) const
		{
			return this->m_RendererID == other.m_RendererID;
		}
	protected:
		ShaderProgram(const uint32_t& ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const uint32_t genShaderProgram() const = 0;
		virtual int getLocation(const std::string& name) = 0;
		std::unordered_map<std::string, int> m_LocationCache = std::unordered_map<std::string, int>();
	};
}
