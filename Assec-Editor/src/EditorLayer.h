#pragma once
#include "include/Assec.h"

namespace assec::editor
{
	class EditorLayer : public assec::layersystem::Layer
	{
	public:
		EditorLayer(const assec::Application& application, graphics::FrameBuffer* frameBuffer);
		~EditorLayer();
		virtual void onEvent(const events::Event& event) override;
		virtual void onAttach() override;
		virtual void onDetach() override;
	private:
		const assec::Application* m_Application;
		graphics::FrameBuffer* m_FrameBuffer;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);

		// TEMP
		assec::ref<assec::graphics::Renderable> m_Renderable, m_RenderableA;
		assec::ref<assec::graphics::Renderer2D> m_Renderer = std::make_shared<assec::graphics::Renderer2D>();
		assec::ref<scene::EditorCamera> m_EditorCamera = std::make_shared<scene::EditorCamera>(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f);

		assec::scene::Scene currentScene = assec::scene::Scene();
	};
} // assec::editor#pragma once
