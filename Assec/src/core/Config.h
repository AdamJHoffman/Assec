#pragma once
#include "graphics/WindowManager.h"
#include "event/Event.h"

#define AC_BIND_FN(fuction) std::bind(&fuction, this, std::placeholders::_1)

#define ASSEC_CORE_TRACE(...)		assec::Logger::CORE_LOGGER->getLogger()->trace(__VA_ARGS__)
#define ASSEC_CORE_INFO(...)		assec::Logger::CORE_LOGGER->getLogger()->info(__VA_ARGS__)
#define ASSEC_CORE_WARNING(...)		assec::Logger::CORE_LOGGER->getLogger()->warn(__VA_ARGS__)
#define ASSEC_CORE_CRITICAL(...)	assec::Logger::CORE_LOGGER->getLogger()->critical(__VA_ARGS__)

#define ASSEC_CLIENT_TRACE(...)		assec::Logger::CLIENT_LOGGER->getLogger()->trace(__VA_ARGS__)
#define ASSEC_CLIENT_INFO(...)		assec::Logger::CLIENT_LOGGER->getLogger()->info(__VA_ARGS__)
#define ASSEC_CLIENT_WARNING(...)	assec::Logger::CLIENT_LOGGER->getLogger()->warn(__VA_ARGS__)
#define ASSEC_CLIENT_CRITICAL(...)	assec::Logger::CLIENT_LOGGER->getLogger()->critical(__VA_ARGS__)


namespace assec
{
	std::shared_ptr<graphics::Window> createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, graphics::EventCallBackFn eventCallBack);
	void init();
	void onEvent(events::Event& event);
	void cleanup();
}
