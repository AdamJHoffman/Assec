#pragma once
#include "include/Assec.h"

#include "EditorApplication.h"

namespace assec::editor
{
	class EditorLayer : public assec::layersystem::Layer
	{
	public:
		EditorLayer(EditorApplication& application);
		~EditorLayer();
		virtual void onEvent(const events::Event& event) override;
		virtual void onAttach() override;
		virtual void onDetach() override;
	private:
		EditorApplication* m_Application;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
	};
} // assec::editor#pragma once
