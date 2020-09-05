﻿#pragma once

// copied from GLFW
#define AC_KEY_UNKNOWN            -1

#define AC_KEY_SPACE              32
#define AC_KEY_APOSTROPHE         39  
#define AC_KEY_COMMA              44  
#define AC_KEY_MINUS              45  
#define AC_KEY_PERIOD             46  
#define AC_KEY_SLASH              47  
#define AC_KEY_0                  48
#define AC_KEY_1                  49
#define AC_KEY_2                  50
#define AC_KEY_3                  51
#define AC_KEY_4                  52
#define AC_KEY_5                  53
#define AC_KEY_6                  54
#define AC_KEY_7                  55
#define AC_KEY_8                  56
#define AC_KEY_9                  57
#define AC_KEY_SEMICOLON          59  
#define AC_KEY_EQUAL              61  
#define AC_KEY_A                  65
#define AC_KEY_B                  66
#define AC_KEY_C                  67
#define AC_KEY_D                  68
#define AC_KEY_E                  69
#define AC_KEY_F                  70
#define AC_KEY_G                  71
#define AC_KEY_H                  72
#define AC_KEY_I                  73
#define AC_KEY_J                  74
#define AC_KEY_K                  75
#define AC_KEY_L                  76
#define AC_KEY_M                  77
#define AC_KEY_N                  78
#define AC_KEY_O                  79
#define AC_KEY_P                  80
#define AC_KEY_Q                  81
#define AC_KEY_R                  82
#define AC_KEY_S                  83
#define AC_KEY_T                  84
#define AC_KEY_U                  85
#define AC_KEY_V                  86
#define AC_KEY_W                  87
#define AC_KEY_X                  88
#define AC_KEY_Y                  89
#define AC_KEY_Z                  90
#define AC_KEY_LEFT_BRACKET       91  
#define AC_KEY_BACKSLASH          92  
#define AC_KEY_RIGHT_BRACKET      93  
#define AC_KEY_GRAVE_ACCENT       96  
#define AC_KEY_WORLD_1            161 
#define AC_KEY_WORLD_2            162 

#define AC_KEY_ESCAPE             256
#define AC_KEY_ENTER              257
#define AC_KEY_TAB                258
#define AC_KEY_BACKSPACE          259
#define AC_KEY_INSERT             260
#define AC_KEY_DELETE             261
#define AC_KEY_RIGHT              262
#define AC_KEY_LEFT               263
#define AC_KEY_DOWN               264
#define AC_KEY_UP                 265
#define AC_KEY_PAGE_UP            266
#define AC_KEY_PAGE_DOWN          267
#define AC_KEY_HOME               268
#define AC_KEY_END                269
#define AC_KEY_CAPS_LOCK          280
#define AC_KEY_SCROLL_LOCK        281
#define AC_KEY_NUM_LOCK           282
#define AC_KEY_PRINT_SCREEN       283
#define AC_KEY_PAUSE              284
#define AC_KEY_F1                 290
#define AC_KEY_F2                 291
#define AC_KEY_F3                 292
#define AC_KEY_F4                 293
#define AC_KEY_F5                 294
#define AC_KEY_F6                 295
#define AC_KEY_F7                 296
#define AC_KEY_F8                 297
#define AC_KEY_F9                 298
#define AC_KEY_F10                299
#define AC_KEY_F11                300
#define AC_KEY_F12                301
#define AC_KEY_F13                302
#define AC_KEY_F14                303
#define AC_KEY_F15                304
#define AC_KEY_F16                305
#define AC_KEY_F17                306
#define AC_KEY_F18                307
#define AC_KEY_F19                308
#define AC_KEY_F20                309
#define AC_KEY_F21                310
#define AC_KEY_F22                311
#define AC_KEY_F23                312
#define AC_KEY_F24                313
#define AC_KEY_F25                314
#define AC_KEY_KP_0               320
#define AC_KEY_KP_1               321
#define AC_KEY_KP_2               322
#define AC_KEY_KP_3               323
#define AC_KEY_KP_4               324
#define AC_KEY_KP_5               325
#define AC_KEY_KP_6               326
#define AC_KEY_KP_7               327
#define AC_KEY_KP_8               328
#define AC_KEY_KP_9               329
#define AC_KEY_KP_DECIMAL         330
#define AC_KEY_KP_DIVIDE          331
#define AC_KEY_KP_MULTIPLY        332
#define AC_KEY_KP_SUBTRACT        333
#define AC_KEY_KP_ADD             334
#define AC_KEY_KP_ENTER           335
#define AC_KEY_KP_EQUAL           336
#define AC_KEY_LEFT_SHIFT         340
#define AC_KEY_LEFT_CONTROL       341
#define AC_KEY_LEFT_ALT           342
#define AC_KEY_LEFT_SUPER         343
#define AC_KEY_RIGHT_SHIFT        344
#define AC_KEY_RIGHT_CONTROL      345
#define AC_KEY_RIGHT_ALT          346
#define AC_KEY_RIGHT_SUPER        347
#define AC_KEY_MENU               348

#define AC_KEY_LAST               AC_KEY_MENU

#define AC_MOUSE_BUTTON_1         0
#define AC_MOUSE_BUTTON_2         1
#define AC_MOUSE_BUTTON_3         2
#define AC_MOUSE_BUTTON_4         3
#define AC_MOUSE_BUTTON_5         4
#define AC_MOUSE_BUTTON_6         5
#define AC_MOUSE_BUTTON_7         6
#define AC_MOUSE_BUTTON_8         7
#define AC_MOUSE_BUTTON_LAST      AC_MOUSE_BUTTON_8
#define AC_MOUSE_BUTTON_LEFT      AC_MOUSE_BUTTON_1
#define AC_MOUSE_BUTTON_RIGHT     AC_MOUSE_BUTTON_2
#define AC_MOUSE_BUTTON_MIDDLE    AC_MOUSE_BUTTON_3

#define AC_CORE_TRACE(...)		assec::Logger::CORE_LOGGER->getLogger()->trace(__VA_ARGS__)
#define AC_CORE_INFO(...)		assec::Logger::CORE_LOGGER->getLogger()->info(__VA_ARGS__)
#define AC_CORE_WARNING(...)	assec::Logger::CORE_LOGGER->getLogger()->warn(__VA_ARGS__)
#define AC_CORE_CRITICAL(...)	assec::Logger::CORE_LOGGER->getLogger()->critical(__VA_ARGS__)

#define AC_CLIENT_TRACE(...)	assec::Logger::CLIENT_LOGGER->getLogger()->trace(__VA_ARGS__)
#define AC_CLIENT_INFO(...)		assec::Logger::CLIENT_LOGGER->getLogger()->info(__VA_ARGS__)
#define AC_CLIENT_WARNING(...)	assec::Logger::CLIENT_LOGGER->getLogger()->warn(__VA_ARGS__)
#define AC_CLIENT_CRITICAL(...)	assec::Logger::CLIENT_LOGGER->getLogger()->critical(__VA_ARGS__)

#ifdef AC_DEBUG
#define TIME_FUNCTION assec::util::Timer timer = assec::util::Timer(__FUNCSIG__)
#ifdef AC_PLATFORM_WINDOWS
#define AC_CLIENT_ASSERT(x, y, ...) {if(!(x)) { AC_CLIENT_CRITICAL(y, __VA_ARGS__); __debugbreak(); } }
#define AC_CLIENT_ASSERT_(x, y) {if(!(x)) { AC_CLIENT_CRITICAL(y); __debugbreak(); } }
#define AC_CORE_ASSERT(x, y, ...) {if(!(x)) { AC_CORE_CRITICAL(y, __VA_ARGS__); __debugbreak(); } }
#define AC_CORE_ASSERT_(x, y) {if(!(x)) { AC_CORE_CRITICAL(y); __debugbreak(); } }
#endif //AC_PLATFORM_WINDOWS
#else //AC_DEBUG
#define TIME_FUNCTION
#define AC_CLIENT_ASSERT(x, ...) x;
#define AC_CORE_ASSERT(x, ...) x;
#define AC_CORE_ASSERT_(x, y) x;
#endif //AC_DEBUG

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
	using ref = std::shared_ptr<T>;

	template<typename T>
	using scope = std::unique_ptr<T>;

	enum class Type
	{
		NONE = 0,
		FLOAT,
		UNSIGNED_INT,
		UNSIGNED_BYTE,
		UNSIGNED_INT_24_8,

		VERTEX_SHADER,
		FRAGMENT_SHADER,

		STATIC_DRAW,
		DYNAMIC_DRAW,

		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,

		LINEAR,
		NEAREST,

		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR,

		RGB,
		RGBA,
		RGBA8,
		DEPTH24_STENCIL8,
		DEPTH_STENCIL,

		COLOR_ATTACHMENT_0,
		DEPTH_STENCIL_ATTACHMENT
	};
}
