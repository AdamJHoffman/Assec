#pragma once
#include "event/Event.h"
#include "event/EventQueue.h"
#include "util/MemoryManager.h"
#include "util/Profiler.h"
#include "util/Loader.h"
#include "Input.h"
#include "Config.h"

void* operator new(size_t size);
void operator delete(void* object, size_t size);

namespace assec
{
	class Assec
	{
	public:
		static Assec& getInstance()
		{
			static Assec assec;
			return assec;
		}
		void onEvent(ref<events::Event> event);
		void handleEvents();
		ref<graphics::WindowManager> AC_WINDOW_MANAGER;
		ref<layersystem::LayerStack> AC_LAYER_STACK;
		ref<events::EventQueue> AC_EVENT_QUEUE;
		ref<InputManager> AC_INPUT_MANAGER;
	private:
		Assec();
		~Assec();
	};
}
