#pragma once
#include "include/Assec.h"

namespace assec::editor
{
	class EditorGuiLayer : public ImGuiLayer
	{
	public:
		EditorGuiLayer(assec::Application& application, graphics::FrameBuffer* frameBuffer);
		~EditorGuiLayer();
		virtual void onEvent0(const events::Event& event) override;
	private:
		graphics::FrameBuffer* m_FrameBuffer;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};
}