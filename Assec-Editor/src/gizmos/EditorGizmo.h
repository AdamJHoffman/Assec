#pragma once

#include "../EditorApplication.h"

namespace assec::editor
{
	class EditorGizmo
	{
	public:
		EditorGizmo(REF(EditorApplication) application) : m_Application(&application) {}
		virtual ~EditorGizmo() = default;
		virtual void render() = 0;
	protected:
		EditorApplication* m_Application = nullptr;
	};
}