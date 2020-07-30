#pragma once
#include "core/Application.h"
#include <imgui.h>

namespace assec
{
	class ImGuiLayer : public assec::layersystem::Layer
	{
	public:
		ImGuiLayer(assec::Application& application);
		~ImGuiLayer();
		virtual void onEvent(const events::Event& event) final override;
		virtual void onAttach() final override;
		virtual void onDetach() final override;
		void BlockEvents(bool block) { this->m_BlockEvents = block; }
	protected:
		virtual void onEvent0(const events::Event& event) = 0;
		void begin();
		void end(const float& deltaTime);
		assec::Application* m_Application;
	private:
		bool m_BlockEvents = true;
	};
} // assec::editor#pragma once