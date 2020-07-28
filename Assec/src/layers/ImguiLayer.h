#pragma once
#include "core/Application.h"
#include <imgui.h>

namespace assec
{
	class ImGuiLayer : public assec::layersystem::Layer
	{
	public:
		ImGuiLayer(const assec::Application& application);
		~ImGuiLayer();
		virtual void onEvent(const events::Event& event) override = 0;
		virtual void onAttach() final override;
		virtual void onDetach() final override;
	protected:
		void begin();
		void end(const float& deltaTime);
		const assec::Application* m_Application;
	};
} // assec::editor#pragma once