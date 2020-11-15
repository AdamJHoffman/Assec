#pragma once

#include "include/Assec.h"

#include "panels/SceneHierarchyPanel.h"
#include "panels/InspectorPanel.h"
#include "panels/NodeEditor.h"

namespace assec::editor
{
	class EditorGuiLayer : public ImGuiLayer
	{
	public:
		EditorGuiLayer(assec::Application& application, ref<graphics::FrameBuffer> frameBuffer);
		~EditorGuiLayer();
		virtual void onEvent0(const events::Event& event) override;
		virtual void onTransaction(const transactions::Transaction& event) override;
		virtual void onAttach0() override;
		virtual void onDetach0() override;
	private:
		void newScene();
		void loadScene();
		void saveSceneAs();
		void saveScene();

		ref<graphics::FrameBuffer> m_FrameBuffer;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		InspectorPanel m_InspectorPanel;
		NodeEditor m_NodeEditor;
	};
}
