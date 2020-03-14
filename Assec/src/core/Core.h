#pragma once
#include "event/Event.h"
#include "util/MemoryManager.h"
#include "util/Profiler.h"
#include "util/Loader.h"
#include "Config.h"

void* operator new(size_t size);
void operator delete(void* object, size_t size);

namespace assec
{
	ref<graphics::Window> createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, graphics::EventCallBackFn eventCallBack);
	void init();
	void cleanup();
}
