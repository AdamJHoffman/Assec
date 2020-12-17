#pragma once

#include "EditorContext.h"

#include "../gizmos/TransformationGizmo.h"

namespace assec::editor
{
	class  ViewportPanel : public EditorContext
	{
	public:
		ViewportPanel(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
			REF(EditorApplication) application);
		~ViewportPanel() = default;
	private:
		virtual void render() override;

		TransformationGizmo gizmo = TransformationGizmo(*this->m_Application);
	};
}