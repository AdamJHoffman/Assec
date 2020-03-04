#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace assec
{
	class Logger
	{
	public:

		Logger(const char* name);
		~Logger();
		inline std::shared_ptr<spdlog::logger>& getLogger() { return this->m_logger; }

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};
}
