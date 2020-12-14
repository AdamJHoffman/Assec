#pragma once

#include "include/Assec.h"
#include "scene/Entity.h"

#include "EditorContext.h"

namespace assec::editor
{
	class InspectorPanel : public EditorContext
	{
	public:
		InspectorPanel(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
			REF(EditorApplication) application);
		~InspectorPanel();
	private:
		virtual void render() override;

		template<typename T, typename UIFunction>
		void drawComponent(const char* name, scene::Entity entity, UIFunction uiFunction);
	};
}
