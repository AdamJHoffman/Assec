﻿#include "acpch.h"
#include "Renderable.h"

namespace assec::graphics
{
	Renderable::~Renderable() { TIME_FUNCTION; }
	Renderable::Renderable(ref<Mesh> mesh, ref<Material> material) : m_Mesh(mesh), m_Material(material) { TIME_FUNCTION; }
	Renderable2D::Renderable2D(ref<Mesh> mesh, ref<Material> material) : Renderable(mesh, material) { TIME_FUNCTION; }
	Renderable2D::~Renderable2D() { TIME_FUNCTION; }
}
