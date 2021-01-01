#include "SceneHierarchyPanel.h"

#include <imgui.h>

namespace assec::editor
{
	SceneHierarchyPanel::SceneHierarchyPanel(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
		std::function<void(CONST_REF(bool))> blockCallback,
		REF(EditorApplication) application)
		: EditorContext(callback, blockCallback, application, "Scene Hierarchy") {}
	SceneHierarchyPanel::~SceneHierarchyPanel() {}
	void SceneHierarchyPanel::render()
	{
		this->m_Application->getActiveScene().reg().each([&](auto entityID)
			{
				scene::Entity entity{ entityID, &this->m_Application->getActiveScene() };
				this->renderEntityNode(entity);
			});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			this->m_Application->m_SelectedEntity = {};
		}

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				this->m_TransactionCallback(std::make_shared<transactions::EntityCreationTransaction>());
			}
			ImGui::EndPopup();
		}

	}
	void SceneHierarchyPanel::renderEntityNode(scene::Entity& entity)
	{
		auto& tag = entity.hasComponent<scene::TagComponent>() ? entity.getComponent<scene::TagComponent>().m_Tag : "N/A";

		ImGuiTreeNodeFlags flags = ((this->m_Application->m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			this->m_Application->m_SelectedEntity = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				if (this->m_Application->m_SelectedEntity == entity)
				{
					this->m_Application->m_SelectedEntity = {};
				}
				this->m_TransactionCallback(std::make_shared<transactions::EntityRemovalTransaction>(entity));
			}

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

}
