#include "SceneHierarchyPanel.h"

namespace assec::editor
{
	SceneHierarchyPanel::SceneHierarchyPanel(scene::Scene& context) : m_Context(&context) {}
	SceneHierarchyPanel::~SceneHierarchyPanel() {}
	void SceneHierarchyPanel::setContext(scene::Scene& context)
	{
		this->m_Context = &context;
	}
	void SceneHierarchyPanel::setSelectionCallback(const std::function<void(const scene::Entity&)>& callback)
	{
		this->m_SelectionCallback = callback;
	}
	void SceneHierarchyPanel::renderImGUI()
	{
		ImGui::Begin("Scene Hierarchy");

		this->m_Context->reg().each([&](auto entityID)
			{
				scene::Entity entity{ entityID, this->m_Context };
				this->renderEntityNode(entity);
			});

		ImGui::End();
	}
	void SceneHierarchyPanel::renderEntityNode(scene::Entity& entity)
	{
		auto& tag = entity.getComponent<scene::TagComponent>().m_Tag;

		ImGuiTreeNodeFlags flags = ((this->m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag);
		if (ImGui::IsItemClicked())
		{
			this->m_SelectedEntity = entity;
			this->m_SelectionCallback(entity);
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

}
