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
		void setTransactionCallback(const std::function<void(ref<transactions::Transaction>)>&);
		template<typename T, typename UIFunction>
		void drawComponent(const char* name, scene::Entity entity, UIFunction uiFunction);
	private:
		scene::Entity m_SelectedEntity = scene::Entity();
		std::function<void(ref<transactions::Transaction>)> m_TransactionCallback;
	};
}
