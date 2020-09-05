#pragma once
#include "include/Assec.h"
#include "scene/Entity.h"

namespace assec::editor
{
	class InspectorPanel
	{
	public:
		InspectorPanel() = default;
		~InspectorPanel();
		void renderImGUI();
		void setSelectedEntity(const scene::Entity&);
	private:
		scene::Entity m_SelectedEntity = scene::Entity();
	};
}
