#pragma once

#include <memory>

#include "core/PlatformDetection.h"

#ifdef AC_DEBUG
	#if defined(AC_PLATFORM_WINDOWS)
		#define AC_DEBUGBREAK() __debugbreak()
	#elif defined(AC_PLATFORM_LINUX)
		#include <signal.h>
		#define AC_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define AC_ENABLE_ASSERTS
#else
	#define AC_DEBUGBREAK()
#endif

#define AC_EXPAND_MACRO(x) x
#define AC_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define MAP(X, A, B, C, D) (X-A)/(B-A) * (D-C) + C

#define INLINE inline
#define CONST_REF(x) const x&
#define REF(x) x&

// TEMP----------------------------------------------------
#define AC_SHADER_TEXTURE_NAME "u_image"
#define AC_SHADER_COLOR_NAME "u_color"
#define AC_SHADER_VIEWPROJECTIONMATRIX_NAME "u_viewProjection"
#define AC_SHADER_TRANSFORM_NAME "u_transform"
//--------------------------------------------------------

#define BATCH_MAX_SIZE 1000000
#define BATCH_MAX_TEXTURES 32


namespace assec
{
	template<typename T>
	using scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr scope<T> makeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ref<T> makeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

} // assec

#include "log/Logger.h"
#include "core/Assert.h"