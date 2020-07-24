#include "acpch.h"
#include "Camera.h"

namespace assec::graphics
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar) : Camera::Camera(glm::ortho(left, right, bottom, top, znear, zfar)) { TIME_FUNCTION; }
	void OrthographicCamera::recalculateViewMatrix()
	{
		TIME_FUNCTION;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->m_Position) * glm::rotate(glm::mat4(1.0f), this->m_Rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), this->m_Rotation.y, glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), this->m_Rotation.z, glm::vec3(0, 0, 1));
		this->m_View = glm::inverse(transform);
	}
}
