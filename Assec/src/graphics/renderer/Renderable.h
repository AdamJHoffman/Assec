#pragma once

#include "graphics/VertexArray.h"
#include "graphics/renderer/Material.h"
#include "Mesh.h"
#include "glm/gtx/string_cast.hpp"

namespace assec::graphics
{
	class Renderable
	{
	public:
		~Renderable();
		const Mesh& m_Mesh;
		const Material& m_Material;
	protected:
		Renderable(const Mesh& mesh, const Material& material);
	};

	class Renderable2D : public Renderable
	{
	public:
		Renderable2D(const Mesh& mesh, const Material& material);
		~Renderable2D();
	};
}
