#pragma once

#include <glm/gtx/string_cast.hpp>

#include "graphics/VertexArray.h"
#include "graphics/renderer/Mesh.h"
#include "graphics/renderer/Material.h"

namespace assec::graphics
{
	class Renderable
	{
	public:
		~Renderable();
		INLINE CONST_REF(Mesh) getMesh() const { return this->m_Mesh; }
		INLINE CONST_REF(Material) getMaterial() const { return this->m_Material; }

		INLINE REF(Mesh) getMesh() { return this->m_Mesh; }
		INLINE REF(Material) getMaterial() { return this->m_Material; }

	protected:
		Renderable(REF(Mesh) mesh, REF(Material) material);
	private:
		Mesh& m_Mesh;
		Material& m_Material;
	};

	class Renderable2D : public Renderable
	{
	public:
		Renderable2D(REF(Mesh) mesh, REF(Material) material);
		~Renderable2D();
	};
} // namespace assec::graphics
