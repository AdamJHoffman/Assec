#pragma once
#include "include/Assec.h"

namespace assec::editor
{
	class EditorGuiLayer : public ImGuiLayer
	{
	public:
		EditorGuiLayer(const assec::Application& application);
		~EditorGuiLayer();
		virtual void onEvent(const events::Event& event) override;
	};
}