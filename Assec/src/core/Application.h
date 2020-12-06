#pragma once
#include "event/EventQueue.h"

#include "layers/LayerStack.h"

#include "scene/Scene.h"

namespace assec
{
	class Application
	{
	public:
		Application(const std::string name = "Assec");
		virtual ~Application();
		void onEvent(ref<events::Event> event);
		void handleEvents();
		void run();
		void close();
		virtual void init() = 0;
		virtual void frame() {}
		ref<layersystem::LayerStack> AC_LAYER_STACK = std::make_shared<layersystem::LayerStack>();
		ref<events::EventQueue> AC_EVENT_QUEUE = std::make_shared<events::EventQueue>();
		ref<scene::Scene> m_ActiveScene = std::make_shared<scene::Scene>();
	private:
		bool m_ShouldClose = false;
		void cleanup() const;
	};
} // namespace assec
