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
		Material(CONST_REF(ref<ShaderProgram>) shaderProgram, CONST_REF(ref<Texture>) texture) : m_ShaderProgram(shaderProgram), m_Texture(texture) { TIME_FUNCTION; }
		Material() { TIME_FUNCTION; }
		~Material() { TIME_FUNCTION; }
		void prepare(CONST_REF(glm::mat4) viewProjectionMatrix = glm::mat4(1.0f)) const;
		INLINE CONST_REF(ShaderProgram) getShaderProgram() const { return *this->m_ShaderProgram; }
		INLINE CONST_REF(Texture) getTexture() const { return *this->m_Texture; }
		
		INLINE REF(ShaderProgram) getShaderProgram() { return *this->m_ShaderProgram; }
		INLINE REF(Texture) getTexture() { return *this->m_Texture; }

		INLINE REF(ref<ShaderProgram>) getRawShaderProgram() { return this->m_ShaderProgram; }
		INLINE REF(ref<Texture>) getRawTexture() { return this->m_Texture; }

	private:
		ref<ShaderProgram> m_ShaderProgram = nullptr;
		ref<Texture> m_Texture = nullptr;
	};
} // namespace assec::graphics
