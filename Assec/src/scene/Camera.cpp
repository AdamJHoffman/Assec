#include "acpch.h"
#include "Camera.h"

namespace assec::scene
{
	Camera::Camera(const glm::mat4& projection) : m_Projection(projection) {}

	EditorCamera::EditorCamera(float left, float right, float bottom, float top, float znear, float zfar) : Camera::Camera(glm::ortho(left, right, bottom, top, znear, zfar)), m_View(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(1.0f))
	{
		TIME_FUNCTION;
	}
	void EditorCamera::recalculateViewMatrix()
	{
		TIME_FUNCTION;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->m_Position) * glm::rotate(glm::mat4(1.0f), this->m_Rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), this->m_Rotation.y, glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), this->m_Rotation.z, glm::vec3(0, 0, 1));
		this->m_View = glm::inverse(transform);
	}
} // assec::scene
