#include "acpch.h"

#include "Material.h"

namespace assec::graphics
{
	void Material::prepare(const glm::mat4& viewProjectionMatrix) const
	{
		TIME_FUNCTION;
		this->m_ShaderProgram->bind();
		this->m_ShaderProgram->loadInt(AC_SHADER_TEXTURE_NAME, 0);
		this->m_ShaderProgram->loadMat4(AC_SHADER_VIEWPROJECTIONMATRIX_NAME, viewProjectionMatrix);
		this->m_Texture->bind();
	}
}
