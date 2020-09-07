#pragma once
#include "event/Event.h"
#include "event/EventQueue.h"
#include "util/MemoryManager.h"
#include "graphics/WindowManager.h"
#include "util/Profiler.h"
#include "util/Loader.h"
#include "layers/LayerStack.h"
#include "Input.h"
#include "scene/Scene.h"
#include "graphics/renderer/Renderer.h"

namespace assec
{
	class Application
	{
	public:
		Application(const char* name = "Assec");
		virtual ~Application();
		const void onEvent(events::Event* event);
		const void handleEvents();
		const void run();
		void close();
		virtual void init() = 0;
		layersystem::LayerStack* AC_LAYER_STACK = new layersystem::LayerStack();
		events::EventQueue* AC_EVENT_QUEUE = new events::EventQueue();
		scene::Scene* m_ActiveScene = new scene::Scene();
	private:
		bool m_ShouldClose = false;
		const void cleanup() const
		{
			delete this->AC_LAYER_STACK;
			delete this->AC_EVENT_QUEUE;
			delete this->m_ActiveScene;
			util::Profiler::getProfiler().endSession();
		}
	};
} // namespace assec
