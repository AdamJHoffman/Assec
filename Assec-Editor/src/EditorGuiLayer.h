#pragma once

#include "include/Assec.h"

#include "EditorApplication.h"
#include "panels/SceneHierarchyPanel.h"
#include "panels/InspectorPanel.h"
#include "panels/NodeEditor.h"
#include "panels/ViewportPanel.h"

#include "gizmos/TransformationGizmo.h"

namespace assec::editor
{
	class EditorGuiLayer : public ImGuiLayer
	{
	public:
		EditorGuiLayer(EditorApplication& application);
		~EditorGuiLayer();
		virtual void onEvent0(const events::Event& event) override;
		virtual void onAttach0() override;
		virtual void onDetach0() override;
	private:
		void newScene();
		void loadScene();
		void saveSceneAs();
		void saveScene();

		EditorApplication* m_Application;
		//bool m_ViewportFocused = false, m_ViewportHovered = false;

		std::vector<ref<EditorContext>> m_OpenContexts;
	};
}
