#pragma once
#include "event/Event.h"
#include "event/EventQueue.h"
#include "util/MemoryManager.h"
#include "util/Profiler.h"
#include "util/Loader.h"
#include "layers/LayerStack.h"
#include "Input.h"

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
		ref<graphics::WindowManager> AC_WINDOW_MANAGER;
		ref<layersystem::LayerStack> AC_LAYER_STACK = std::make_shared<layersystem::LayerStack>();
		ref<events::EventQueue> AC_EVENT_QUEUE = std::make_shared<events::EventQueue>();
		ref<InputManager> AC_INPUT_MANAGER = std::make_shared<InputManager>();
	private:
		bool m_ShouldClose = false;
		const void cleanup() const
		{
			util::Profiler::getProfiler().endSession();
		}
	};
} // namespace assec