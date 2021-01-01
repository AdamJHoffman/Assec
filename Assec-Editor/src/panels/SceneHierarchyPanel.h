#pragma once
#include "include/Assec.h"
#include "scene/Entity.h"

#include "EditorContext.h"

namespace assec::editor
{
	class SceneHierarchyPanel : public EditorContext
	{
	public:
		SceneHierarchyPanel(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
			std::function<void(CONST_REF(bool))> blockCallback,
			REF(EditorApplication) application);
		~SceneHierarchyPanel();
	private:
		virtual void render() override;
		void renderEntityNode(scene::Entity& entity);
	};
}
