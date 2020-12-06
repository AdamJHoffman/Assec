#pragma once

#include "core/Application.h"

namespace assec
{
	class ImGuiLayer : public assec::layersystem::Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void onEvent(const events::Event& event) final override;
		virtual void onAttach() final override;
		virtual void onDetach() final override;
		void BlockEvents(bool block) { this->m_BlockEvents = block; }
		void setDarkThemecolors();
	protected:
		virtual void onEvent0(const events::Event& event) = 0;
		virtual void onAttach0() = 0;
		virtual void onDetach0() = 0;
		void begin();
		void end(const float& deltaTime);
	private:
		bool m_BlockEvents = true;
	};
} // assec::editor#pragma once
