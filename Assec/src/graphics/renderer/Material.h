#pragma once
#include "graphics/VertexArray.h"
#include "graphics/Texture.h"

namespace assec::graphics
{
	class Material
	{
	public:
		Material(ref<VertexArray> vertexArray, ref<Texture> texture);
		~Material();
		ref<VertexArray> m_VertexArray;
		ref<Texture> m_Texture;
	};
}
