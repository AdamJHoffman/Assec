#include "acpch.h"

#include "Logger.h"

namespace assec
{
	Logger::Logger(CONST_REF(std::string) name) : m_Logger(spdlog::stdout_color_mt(name.c_str()))
	{
		TIME_FUNCTION;
		this->m_Logger->set_pattern("[%H:%M:%S] [%n] : %v");
		this->m_Logger->set_level(spdlog::level::trace);
	}
	Logger::~Logger() { TIME_FUNCTION; }
	ref<Logger> Logger::CORE_LOGGER = std::make_shared<Logger>("CORE");
	ref<Logger> Logger::CLIENT_LOGGER = std::make_shared<Logger>("CLIENT");
} // namespace assec
