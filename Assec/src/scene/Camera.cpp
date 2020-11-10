#include "acpch.h"

#include "Camera.h"

namespace assec::scene
{
	Camera::Camera(const glm::mat4& projection) : m_Projection(projection) {}
} // assec::scene
