#include "InspectorPanel.h"
#include "scene/Components.h"

namespace assec::editor
{
	InspectorPanel::~InspectorPanel() {}
	void InspectorPanel::setSelectedEntity(const scene::Entity& entity)
	{
		this->m_SelectedEntity = entity;
	}
	void InspectorPanel::renderImGUI()
	{
		ImGui::Begin("Inspector");
		if (this->m_SelectedEntity.operator bool())
		{
			ImGui::BeginChild("Tag Component", ImVec2(ImGui::GetContentRegionAvailWidth(), 29), true);
			ImGui::Text(this->m_SelectedEntity.getComponent<scene::TagComponent>().m_Tag);
			ImGui::EndChild();
		}
		ImGui::End();
	}
}
