#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include "core/Base.h"
#include "util/Profiler.h"

#define AC_CORE_TRACE(...)		assec::Logger::CORE_LOGGER->getLogger()->trace(__VA_ARGS__)
#define AC_CORE_INFO(...)		assec::Logger::CORE_LOGGER->getLogger()->info(__VA_ARGS__)
#define AC_CORE_WARNING(...)	assec::Logger::CORE_LOGGER->getLogger()->warn(__VA_ARGS__)
#define AC_CORE_CRITICAL(...)	assec::Logger::CORE_LOGGER->getLogger()->critical(__VA_ARGS__)

#define AC_CLIENT_TRACE(...)	assec::Logger::CLIENT_LOGGER->getLogger()->trace(__VA_ARGS__)
#define AC_CLIENT_INFO(...)		assec::Logger::CLIENT_LOGGER->getLogger()->info(__VA_ARGS__)
#define AC_CLIENT_WARNING(...)	assec::Logger::CLIENT_LOGGER->getLogger()->warn(__VA_ARGS__)
#define AC_CLIENT_CRITICAL(...)	assec::Logger::CLIENT_LOGGER->getLogger()->critical(__VA_ARGS__)

namespace assec
{
	class Logger
	{
	public:
		static ref<Logger> CORE_LOGGER;
		static ref<Logger> CLIENT_LOGGER;

		Logger(const std::string& name);
		~Logger();
		inline const ref<spdlog::logger>& getLogger() const { TIME_FUNCTION; return this->m_Logger; }
	private:
		ref<spdlog::logger> m_Logger;
	};
}
