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
		void onEvent(events::Event* event);
		void handleEvents();
		void run();
		void close();
		virtual void init() = 0;
		layersystem::LayerStack* AC_LAYER_STACK = new layersystem::LayerStack();
		events::EventQueue* AC_EVENT_QUEUE = new events::EventQueue();
		ref<scene::Scene> m_ActiveScene = std::make_shared<scene::Scene>();
	private:
		bool m_ShouldClose = false;
		void cleanup() const;
	};
} // namespace assec
