#pragma once

#define AC_CORE_TRACE(...)		assec::Logger::CORE_LOGGER->getLogger()->trace(__VA_ARGS__)
#define AC_CORE_INFO(...)		assec::Logger::CORE_LOGGER->getLogger()->info(__VA_ARGS__)
#define AC_CORE_WARNING(...)	ssec::Logger::CORE_LOGGER->getLogger()->warn(__VA_ARGS__)
#define AC_CORE_CRITICAL(...)	assec::Logger::CORE_LOGGER->getLogger()->critical(__VA_ARGS__)

#define AC_CLIENT_TRACE(...)	assec::Logger::CLIENT_LOGGER->getLogger()->trace(__VA_ARGS__)
#define AC_CLIENT_INFO(...)		assec::Logger::CLIENT_LOGGER->getLogger()->info(__VA_ARGS__)
#define AC_CLIENT_WARNING(...)	assec::Logger::CLIENT_LOGGER->getLogger()->warn(__VA_ARGS__)
#define AC_CLIENT_CRITICAL(...)	assec::Logger::CLIENT_LOGGER->getLogger()->critical(__VA_ARGS__)

#ifdef AC_DEBUG
#define TIME_FUNCTION assec::util::Timer timer = assec::util::Timer(__FUNCSIG__)
#ifdef AC_PLATFORM_WINDOWS
#define AC_CLIENT_ASSERT(x, y, ...) {if(!(x)) { AC_CLIENT_CRITICAL(y, __VA_ARGS__); __debugbreak(); } }
#define AC_CORE_ASSERT(x, y, ...) {if(!(x)) { AC_CORE_CRITICAL(y, __VA_ARGS__); __debugbreak(); } }
#endif //AC_PLATFORM_WINDOWS
#else //AC_DEBUG
#define TIME_FUNCTION
#define AC_CLIENT_ASSERT(x, ...)
#define AC_CORE_ASSERT(x, ...)
#endif //AC_DEBUG

namespace assec
{
	template<typename T>
	using ref = std::shared_ptr<T>;

	template<typename T>
	using scope = std::unique_ptr<T>;
}
