#include "acpch.h"
#include "Material.h"

namespace assec::graphics
{
	Material::Material(ref<ShaderProgram> shaderProgram, ref<Texture> texture) : m_ShaderProgram(shaderProgram), m_Texture(texture) {}
	Material::~Material() {}
	void Material::prepare(glm::mat4& viewProjectionMatrix) const
	{
		this->m_ShaderProgram->bind();
		this->m_ShaderProgram->loadInt(AC_SHADER_TEXTURE_NAME, 0);
		this->m_ShaderProgram->loadMat4(AC_SHADER_VIEWPROJECTIONMATRIX_NAME, viewProjectionMatrix);
		this->m_Texture->bind();
	}
	//TexturedMaterial::TexturedMaterial(ref<ShaderProgram> shaderProgram, ref<Texture> texture) : Material::Material(shaderProgram), m_Texture(texture) {}
	//TexturedMaterial::~TexturedMaterial() {}
	//void TexturedMaterial::prepare(glm::mat4& viewProjectionMatrix) const
	//{
	//	this->m_ShaderProgram->bind();
	//	this->m_ShaderProgram->loadInt(AC_SHADER_TEXTURE_NAME, 0);
	//	this->m_ShaderProgram->loadMat4(AC_SHADER_VIEWPROJECTIONMATRIX_NAME, viewProjectionMatrix);
	//	this->m_Texture->bind();
	//}
	//ColoredMaterial::ColoredMaterial(ref<ShaderProgram> shaderProgram, glm::vec4 color) : Material::Material(shaderProgram), m_Color(color) {}
	//ColoredMaterial::~ColoredMaterial() {}
	//void ColoredMaterial::prepare(glm::mat4& viewProjectionMatrix) const
	//{
	//	this->m_ShaderProgram->bind();
	//	this->m_ShaderProgram->loadVec4(AC_SHADER_COLOR_NAME, this->m_Color);
	//	this->m_ShaderProgram->loadMat4(AC_SHADER_VIEWPROJECTIONMATRIX_NAME, viewProjectionMatrix);
	//}
}
