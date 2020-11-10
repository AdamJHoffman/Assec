#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace assec::scene
{
	class Camera
	{
	public:
		enum class projectionType { ORTHOGRAPHIC, PERSPECTIVE };
		Camera() = default;
		Camera(const Camera& other) = default;
		virtual ~Camera() = default;
		Camera(const glm::mat4& projection);
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
} //assec::scene
