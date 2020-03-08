#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace assec
{
	class Logger
	{
	public:
		static std::shared_ptr<Logger> CORE_LOGGER;
		static std::shared_ptr<Logger> CLIENT_LOGGER;

		Logger(const char* name);
		~Logger();
		inline const std::shared_ptr<spdlog::logger>& getLogger() const { return this->m_logger; }
	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};
}
