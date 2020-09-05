#pragma once
#include "include/Assec.h"
#include "scene/Entity.h"
#include "InspectorPanel.h"

namespace assec::editor
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(scene::Scene&);
		~SceneHierarchyPanel();
		void setContext(scene::Scene&);
		void setSelectionCallback(const std::function<void(const scene::Entity&)>&);
		void renderImGUI();
	private:
		void renderEntityNode(scene::Entity& entity);
		scene::Scene* m_Context = nullptr;
		scene::Entity m_SelectedEntity;
		std::function<void(const scene::Entity&)> m_SelectionCallback;
	};
}
