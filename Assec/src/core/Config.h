#pragma once

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

	enum class KEY
	{
		KEY_UNKNOWN = -1,
		KEY_SPACE,
		KEY_APOSTROPHE,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON,
		KEY_EQUAL,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LEFT_BRACKET,
		KEY_BACKSLASH,
		KEY_RIGHT_BRACKET,
		KEY_GRAVE_ACCENT,
		KEY_WORLD_1,
		KEY_WORLD_2,
		KEY_ESCAPE,
		KEY_ENTER,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_INSERT,
		KEY_DELETE,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_CAPS_LOCK,
		KEY_SCROLL_LOCK,
		KEY_NUM_LOCK,
		KEY_PRINT_SCREEN,
		KEY_PAUSE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_F16,
		KEY_F17,
		KEY_F18,
		KEY_F19,
		KEY_F20,
		KEY_F21,
		KEY_F22,
		KEY_F23,
		KEY_F24,
		KEY_F25,
		KEY_KP_0,
		KEY_KP_1,
		KEY_KP_2,
		KEY_KP_3,
		KEY_KP_4,
		KEY_KP_5,
		KEY_KP_6,
		KEY_KP_7,
		KEY_KP_8,
		KEY_KP_9,
		KEY_KP_DECIMAL,
		KEY_KP_DIVIDE,
		KEY_KP_MULTIPLY,
		KEY_KP_SUBTRACT,
		KEY_KP_ADD,
		KEY_KP_ENTER,
		KEY_KP_EQUAL,
		KEY_LEFT_SHIFT,
		KEY_LEFT_CONTROL,
		KEY_LEFT_ALT,
		KEY_LEFT_SUPER,
		KEY_RIGHT_SHIFT,
		KEY_RIGHT_CONTROL,
		KEY_RIGHT_ALT,
		KEY_RIGHT_SUPER,
		KEY_MENU,
		KEY_LAST,
	};

	enum class MOUSE
	{
		MOUSE_BUTTON_1 = 0,
		MOUSE_BUTTON_2,
		MOUSE_BUTTON_3,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_8,
		MOUSE_BUTTON_LAST,
		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE
	};

	enum class Type
	{
		NONE = 0,
		FLOAT,
		UNSIGNED_INT,
		UNSIGNED_BYTE,
		UNSIGNED_INT_24_8,

		VERTEX_SHADER,
		FRAGMENT_SHADER,

		DEPTH_TEST,
		LESS,

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
} // assec
