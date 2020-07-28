#pragma once
#include "include/Assec.h"
#include "core/Application.h"

namespace assec::editor
{
	class EditorLayer : public assec::layersystem::Layer
	{
	public:
		EditorLayer(const assec::Application& application);
		~EditorLayer();
		virtual void onEvent(const events::Event& event) override;
		virtual void onAttach() override;
		virtual void onDetach() override;
	private:
		const assec::Application* m_Application;

		// TEMP
		assec::ref<assec::graphics::Renderable> m_Renderable, m_RenderableA;
		assec::ref<assec::graphics::Camera> m_Camera = std::make_shared<assec::graphics::OrthographicCamera>(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f);
		assec::ref<assec::graphics::Renderer2D> m_Renderer = std::make_shared<assec::graphics::Renderer2D>();
	};
} // assec::editor#pragma once
