#pragma once
#include <glm/glm.hpp>

namespace assec::graphics
{
	class Camera
	{
	public:
		~Camera() { TIME_FUNCTION; }
		void setPosition(const glm::vec3 position) { TIME_FUNCTION; this->m_Position = position; recalculateViewMatrix(); }
		void setRotation(const glm::vec3 rotation) { TIME_FUNCTION; this->m_Rotation = rotation; recalculateViewMatrix(); }
		inline const glm::vec3 getPosition() const { TIME_FUNCTION; return this->m_Position; }
		inline const glm::vec3 getRotation() const { TIME_FUNCTION; return this->m_Rotation; }
		inline const glm::mat4 getViewMatrix() const { TIME_FUNCTION; return this->m_View; }
		inline const glm::mat4 getProjectionMatrix() const { TIME_FUNCTION; return this->m_Projection; }
		inline const glm::mat4 getViewProjectionMatrix() const { TIME_FUNCTION; return this->m_Projection * this->m_View; }
	protected:
		Camera(glm::mat4 projection) : m_Projection(projection), m_View(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(1.0f)) { TIME_FUNCTION; }
		virtual void recalculateViewMatrix() = 0;
		glm::mat4 m_Projection, m_View;
		glm::vec3 m_Position, m_Rotation;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar);
	protected:
		virtual void recalculateViewMatrix() override;
	};
}
