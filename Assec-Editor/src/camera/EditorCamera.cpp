#include "EditorCamera.h"

#define _USE_MATH_DEFINES
#include <math.h>

#pragma warning(push, 0)	// Disable warnings in external header
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

#include "event/EngineEvents.h"
#include "event/WindowEvents.h"
#include "event/MouseEvents.h"

#include "util/misc.h"
#include "util/Dispatcher.h"

#include "input/Input.h"

#include "graphics/WindowManager.h"

namespace assec::editor
{
	void EditorCamera::onEvent(const events::Event& event)
	{
		util::Dispatcher dispatcher = util::Dispatcher(event);
		dispatcher.dispatch<events::WindowResizeEvent>([this](const events::WindowResizeEvent& event)
			{
				this->setViewportSize(event.getSize().x, event.getSize().y);
				return false;
			});
		dispatcher.dispatch<events::MouseScrolledEvent>([this](const events::MouseScrolledEvent& event)
			{	
				float delta = event.getOffset().y * 0.1f;
				this->mouseZoom(delta);
				this->updateView();
				return false;
			});
		dispatcher.dispatch<events::MouseMovedEvent>([this](const events::MouseMovedEvent& event)
			{
				glm::vec2 mouseDelta = (this->m_InitialMousePosition - event.getPosition()) * 0.005f;
				this->m_InitialMousePosition = event.getPosition();
				if (input::Input::isKeyDown(KEY::KEY_LEFT_ALT) || input::Input::isKeyDown(KEY::KEY_RIGHT_ALT))
				{
					if (input::Input::isMouseButtonDown(MOUSE::MOUSE_BUTTON_MIDDLE))
						this->mousePan(-mouseDelta);
					else if (input::Input::isMouseButtonDown(MOUSE::MOUSE_BUTTON_LEFT))
						this->mouseRotate(mouseDelta);
					else if (input::Input::isMouseButtonDown(MOUSE::MOUSE_BUTTON_RIGHT))
						this->mouseZoom(mouseDelta.x);
					this->updateView();
				}
				return false;
			});
	}

	void EditorCamera::updateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void EditorCamera::updateView()
	{
		m_Position = calculatePosition();

		glm::quat orientation = getOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	std::pair<float, float> EditorCamera::panSpeed() const
	{
		float x = std::min<float>(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min<float>(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::rotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::zoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max<float>(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min<float>(speed, 100.0f); // max speed = 100
		return speed;
	}

	void EditorCamera::mousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = panSpeed();
		m_FocalPoint += -getRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += getUpDirection() * delta.y * ySpeed * m_Distance;
	}

	void EditorCamera::mouseRotate(const glm::vec2& delta)
	{
		float yawSign = getUpDirection().y < 0 ? 1.0f : -1.0f;
		m_Yaw += yawSign * delta.x * rotationSpeed();
		m_Pitch -= delta.y * rotationSpeed();
	}

	void EditorCamera::mouseZoom(float delta)
	{
		m_Distance += delta * zoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += getForwardDirection();
			m_Distance = 1.0f;
		}
	}

	glm::vec3 EditorCamera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::calculatePosition() const
	{
		return m_FocalPoint - getForwardDirection() * m_Distance;
	}

	glm::quat EditorCamera::getOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
}