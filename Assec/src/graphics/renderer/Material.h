#pragma once

#include <glm/glm.hpp>

#include "graphics/VertexArray.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"

namespace assec::graphics
{
	class Material
	{
	public:
		Material(const ref<ShaderProgram>& shaderProgram, const ref<Texture>& texture) : m_ShaderProgram(shaderProgram), m_Texture(texture) { TIME_FUNCTION; }
		Material() { TIME_FUNCTION; }
		~Material() { TIME_FUNCTION; }
		void prepare(const glm::mat4& viewProjectionMatrix = glm::mat4(1.0f)) const;
		ref<ShaderProgram> m_ShaderProgram = nullptr;
		ref<Texture> m_Texture = nullptr;
	};
}
