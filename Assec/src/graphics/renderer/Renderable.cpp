#include "acpch.h"
#include "Renderable.h"

namespace assec::graphics
{
	Renderable::~Renderable() { TIME_FUNCTION; }
	Renderable::Renderable(const Mesh& mesh, const Material& material) : m_Mesh(mesh), m_Material(material) { TIME_FUNCTION; }
	Renderable2D::Renderable2D(const Mesh& mesh, const Material& material) : Renderable(mesh, material) { TIME_FUNCTION; }
	Renderable2D::~Renderable2D() { TIME_FUNCTION; }
}
