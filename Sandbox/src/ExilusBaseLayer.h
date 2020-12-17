#pragma once
#include "include/Assec.h"

namespace exilus
{
	class ExilusBaseLayer : public assec::layersystem::Layer
	{
	public:
		ExilusBaseLayer(assec::Application& application);
		~ExilusBaseLayer();
		virtual void onEvent(const assec::events::Event& event) override;
		virtual void onAttach() override;
		virtual void onDetach() override;
	private:
		assec::Application* m_Application;
	};
} // assec::editor
