#include "TransformationGizmo.h"

#include "util/Dispatcher.h"

#include "input/Input.h"

#include "math/Math.h"

namespace assec::editor
{
	void TransformationGizmo::render()
	{
		ImGuizmo::Enable(true);
		if(input::Input::isKeyDown(KEY::KEY_Q))
			this->m_CurrentGizmoOperation = ImGuizmo::ROTATE;
		if (input::Input::isKeyDown(KEY::KEY_W))
			this->m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
		if (input::Input::isKeyDown(KEY::KEY_E))
			this->m_CurrentGizmoOperation = ImGuizmo::SCALE;
		if (this->m_Application->m_SelectedEntity)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			glm::mat4 view = this->m_Application->m_Camera.getViewMatrix();
			const glm::mat4& projection = this->m_Application->m_Camera.m_Projection;

			auto& transformComponent = this->m_Application->m_SelectedEntity.getComponent<scene::TransformComponent>();
			glm::mat4& transform = transformComponent.toMatrix();

			bool snap = input::Input::isKeyDown(KEY::KEY_LEFT_CONTROL);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (m_CurrentGizmoOperation == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection),
				m_CurrentGizmoOperation, this->m_CurrentGizmoMode, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				math::decomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - transformComponent.rotation;
				transformComponent.translation = translation;
				transformComponent.rotation += deltaRotation;
				transformComponent.scale = scale;
			}
		}
	}
}