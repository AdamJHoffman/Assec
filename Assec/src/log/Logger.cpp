#include "acpch.h"
#include "Logger.h"

namespace assec
{

	Logger::Logger(const char* name) : m_logger(spdlog::stdout_color_mt(name))
	{
		this->m_logger->set_pattern("[%H:%M:%S] [%n] : %v");
		this->m_logger->set_level(spdlog::level::trace);
	}
	Logger::~Logger() {}
	std::shared_ptr<Logger> Logger::CORE_LOGGER = std::make_shared<Logger>("CORE");
	std::shared_ptr<Logger> Logger::CLIENT_LOGGER = std::make_shared<Logger>("CLIENT");
}