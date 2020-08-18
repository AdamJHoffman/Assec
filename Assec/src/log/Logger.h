#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include "core/Config.h"

namespace assec
{
	class Logger
	{
	public:
		static ref<Logger> CORE_LOGGER;
		static ref<Logger> CLIENT_LOGGER;

		Logger(const char* name);
		~Logger();
		inline const ref<spdlog::logger>& getLogger() const { TIME_FUNCTION; return this->m_logger; }
	private:
		ref<spdlog::logger> m_logger;
	};
}
