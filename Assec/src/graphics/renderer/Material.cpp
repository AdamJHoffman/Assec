#include "acpch.h"
#include "Material.h"

namespace assec::graphics
{
	Material::Material(ref<VertexArray> vertexArray, ref<Texture> texture) : m_VertexArray(vertexArray), m_Texture(texture) {}
	Material::~Material() {}
}