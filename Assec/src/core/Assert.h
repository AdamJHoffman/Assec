#pragma once

#include "core/Base.h"
#include "log/Logger.h"
#include <filesystem>

#ifdef AC_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define AC_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { AC##type##CRITICAL(msg, __VA_ARGS__); AC_DEBUGBREAK(); } }
#define AC_INTERNAL_ASSERT_WITH_MSG(type, check, ...) AC_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define AC_INTERNAL_ASSERT_NO_MSG(type, check) AC_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", AC_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
		
#define AC_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define AC_INTERNAL_ASSERT_GET_MACRO(...) AC_EXPAND_MACRO( AC_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, AC_INTERNAL_ASSERT_WITH_MSG, AC_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define AC_ASSERT(...) AC_EXPAND_MACRO( AC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CLIENT_, __VA_ARGS__) )
#define AC_CORE_ASSERT(...) AC_EXPAND_MACRO( AC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else	
#define AC_ASSERT(x, ...) x
#define AC_CORE_ASSERT(x, ...) x
#endif