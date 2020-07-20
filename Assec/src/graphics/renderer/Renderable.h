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
		~Renderable() {}
		ref<Mesh> m_Mesh;
		ref<Material> m_Material;
	protected:
		Renderable(ref<Mesh> mesh, ref<Material> material) : m_Mesh(mesh), m_Material(material) {}
	};

	class Renderable2D : public Renderable
	{
	public:
		Renderable2D(ref<Mesh> mesh, ref<Material> material) : Renderable(mesh, material) {}
		~Renderable2D() {}
	};
}