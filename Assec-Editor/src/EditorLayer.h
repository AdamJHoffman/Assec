#pragma once
#include "include/Assec.h"

namespace assec::editor
{
	class EditorLayer : public assec::layersystem::Layer
	{
	public:
		EditorLayer(const assec::Application& application, ref<graphics::FrameBuffer> frameBuffer);
		~EditorLayer();
		virtual void onEvent(const events::Event& event) override;
		virtual void onTransaction(const transactions::Transaction& event) override;
		virtual void onAttach() override;
		virtual void onDetach() override;
	private:
		const assec::Application* m_Application;
		ref<graphics::FrameBuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);

		// TEMP
		//assec::ref<scene::EditorCamera> m_EditorCamera = std::make_shared<scene::EditorCamera>(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f);
	};
} // assec::editor#pragma once
