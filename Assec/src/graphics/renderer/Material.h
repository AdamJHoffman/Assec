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
		Material(ShaderProgram& shaderProgram, Texture& texture);
		~Material();
		void prepare(glm::mat4& viewProjectionMatrix = glm::mat4(1.0f)) const;
		ShaderProgram& m_ShaderProgram;
		Texture& m_Texture;
	};
}
