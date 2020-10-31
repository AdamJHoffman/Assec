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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			this->m_SelectedEntity = {};
			this->m_SelectionCallback(this->m_SelectedEntity);
		}

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->createEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();
	}
	void SceneHierarchyPanel::renderEntityNode(scene::Entity& entity)
	{
		auto& tag = entity.hasComponent<scene::TagComponent>() ? entity.getComponent<scene::TagComponent>().m_Tag : "N/A";

		ImGuiTreeNodeFlags flags = ((this->m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			this->m_SelectedEntity = entity;
			this->m_SelectionCallback(entity);
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->destroyEntity(entity);
			if (this->m_SelectedEntity == entity)
				this->m_SelectedEntity = {};
		}
	}

}
