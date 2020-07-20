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
		~Material() {}
		virtual void prepare(glm::mat4& viewProjectionMatrix = glm::mat4(1.0f)) const = 0;
		ref<ShaderProgram> m_ShaderProgram;
	protected:
		Material(ref<ShaderProgram> shaderProgram) : m_ShaderProgram(shaderProgram) {}
	};

	class TexturedMaterial : public Material
	{
	public:
		TexturedMaterial(ref<ShaderProgram> shaderProgram, ref<Texture> texture);
		~TexturedMaterial();
		virtual void prepare(glm::mat4& viewProjectionMatrix) const override;
		ref<Texture> m_Texture;
	};

	class ColoredMaterial : public Material
	{
	public:
		ColoredMaterial(ref<ShaderProgram> shaderProgram, glm::vec4 color = glm::vec4(1.0f));
		~ColoredMaterial();
		virtual void prepare(glm::mat4& viewProjectionMatrix) const override;
		glm::vec4 m_Color;
	};
}
