#pragma once

#include "Mesh.h"

#include <glm/gtx/string_cast.hpp>

#include "graphics/VertexArray.h"
#include "graphics/renderer/Material.h"

namespace assec::graphics
{
	class Renderable
	{
	public:
		~Renderable();
		Mesh& m_Mesh;
		Material& m_Material;
	protected:
		Renderable(Mesh& mesh, Material& material);
	};

	class Renderable2D : public Renderable
	{
	public:
		Renderable2D(Mesh& mesh, Material& material);
		~Renderable2D();
	};
}
