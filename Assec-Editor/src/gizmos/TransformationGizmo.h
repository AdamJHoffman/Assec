#pragma once

#include <imgui.h>
#include <ImGuizmo.h>

#include "EditorGizmo.h"

namespace assec::editor
{
	class TransformationGizmo : public EditorGizmo
	{
	public:
		TransformationGizmo(REF(EditorApplication) application) : EditorGizmo(application) {}
		~TransformationGizmo() = default;
		virtual void render() override;
	private:
		ImGuizmo::OPERATION m_CurrentGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE m_CurrentGizmoMode = ImGuizmo::MODE::LOCAL;
	};
}