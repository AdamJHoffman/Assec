﻿#pragma once

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
		Shader(CONST_REF(uint32_t) ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const uint32_t genShader(const Type& type) const = 0;
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() { TIME_FUNCTION; }
		ShaderProgram(CONST_REF(ShaderProgram) other)
			: m_RendererID(other.m_RendererID), m_LocationCache(other.m_LocationCache) {}
		virtual void bind() const = 0;
		virtual void loadInt(CONST_REF(std::string) name, CONST_REF(int) value) = 0;
		virtual void loadIntArray(CONST_REF(std::string) name, CONST_REF(size_t) size, const int* value) = 0;
		virtual void loadVec4(CONST_REF(std::string) name, CONST_REF(glm::vec4) value) = 0;
		virtual void loadMat4(CONST_REF(std::string) name, CONST_REF(glm::mat4) value) = 0;
		uint32_t m_RendererID;
		bool operator==(CONST_REF(ShaderProgram) other) const
		{
			TIME_FUNCTION;
			return this->m_RendererID == other.m_RendererID;
		}
	protected:
		ShaderProgram(CONST_REF(uint32_t) ID) : m_RendererID(ID) { TIME_FUNCTION; }
		virtual const uint32_t genShaderProgram() const = 0;
		virtual int getLocation(CONST_REF(std::string) name) = 0;
		std::unordered_map<std::string, int> m_LocationCache = std::unordered_map<std::string, int>();
	};
}
