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
		const void onEvent(ref<events::Event> event);
		const void handleEvents();
		const void run();
		void close();
		virtual void init() = 0;
		ref<layersystem::LayerStack> AC_LAYER_STACK = std::make_shared<layersystem::LayerStack>();
		ref<events::EventQueue> AC_EVENT_QUEUE = std::make_shared<events::EventQueue>();
		ref<scene::Scene> m_ActiveScene = std::make_shared<scene::Scene>();
	private:
		bool m_ShouldClose = false;
		const void cleanup() const
		{
			util::Profiler::getProfiler().endSession();
		}
	};
} // namespace assec
