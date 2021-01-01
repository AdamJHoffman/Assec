#pragma once

namespace assec
{
	enum class KEY
	{
		KEY_UNKNOWN = 0,
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
	};

	enum class MOUSE
	{
		MOUSE_BUTTON_UNKNOWN = 0,
		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_8,		
	};

	enum class Usage
	{
		NONE = 0,
		STREAM_DRAW,
		STATIC_DRAW,
		DYNAMIC_DRAW,
		STREAM_READ,
		STATIC_READ,
		DYNAMIC_READ
	};

	enum class Access
	{
		NONE = 0,
		READ_ONLY,
		WRITE_ONLY, 
		READ_WRITE 
	};

	enum class BufferTarget
	{
		NONE = 0,
		ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER
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
		BLEND,
		SRC_ALPHA, 
		ONE_MINUS_SRC_ALPHA,

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

		RED,
		RED_INTEGER,
		R8,
		R32UI,
		R32I,
		RG,
		RG8,
		RGB,
		RGB8,
		RGBA,
		RGBA8,
		DEPTH24_STENCIL8,
		DEPTH_STENCIL,

		COLOR_ATTACHMENT0,
		COLOR_ATTACHMENT1,
		DEPTH_STENCIL_ATTACHMENT
	};

	enum class AnglePlatformType
	{
		NONE = 0,
		OPENGL,
		OPENGLES,
		D3D9,
		D3D11,
		VULKAN,
		METAL
	};

	enum class CursorType
	{
		ARROW = 0,
		IBEAM,
		CROSSHAIR,
		POINTING_HAND,
		RESIZE_EW,
		RESIZE_NS,
		RESIZE_NWSE,
		RESIZE_NESW,
		RESIZE_ALL,
		NOT_ALLOWED,
		HRESIZE,
		VRESIZE,
		HAND
	};

	enum class CursorMode
	{
		NORMAL = 0,
		HIDDEN,
		DISABLED,
	};

	enum class JoyStickHatSate
	{
		CENTERED,
		UP,
		RIGHT,
		DOWN,
		LEFT,
		RIGHT_UP,
		RIGHT_DOWN,
		LEFT_UP,
		LEFT_DOWN
	};

	enum class Modkeys
	{
		SHIFT = 0,
		CONTROL,
		ALT,
		SUPER,
		CAPS_LOCK,
		NUM_LOCK
	};

	enum class JoystickID
	{
		JOYSTICK_1 = 0,
		JOYSTICK_2,
		JOYSTICK_3,
		JOYSTICK_4,
		JOYSTICK_5,
		JOYSTICK_6,
		JOYSTICK_7,
		JOYSTICK_8,
		JOYSTICK_9,
		JOYSTICK_10,
		JOYSTICK_11,
		JOYSTICK_12,
		JOYSTICK_13,
		JOYSTICK_14,
		JOYSTICK_15,
		JOYSTICK_16
	};

	enum class GamepadButton
	{
		BUTTON_A = 0,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_LEFT_BUMPER,
		BUTTON_RIGHT_BUMPER,
		BUTTON_BACK,
		BUTTON_START,
		BUTTON_GUIDE,
		BUTTON_LEFT_THUMB,
		BUTTON_RIGHT_THUMB,
		BUTTON_DPAD_UP,
		BUTTON_DPAD_RIGHT,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_LEFT
	};

	enum class GamepadAxis
	{
		AXIS_LEFT_X = 0,
		AXIS_LEFT_Y,
		AXIS_RIGHT_X,
		AXIS_RIGHT_Y,
		AXIS_LEFT_TRIGGER,
		AXIS_RIGHT_TRIGGER,
	};

	enum class WindowAttribute
	{
		FOCUSED,
		ICONIFIED,
		RESIZABLE,
		VISIBLE,
		DECORATED,
		AUTO_ICONIFY,
		FLOATING,
		MAXIMIZED,
		CENTER_CURSOR,
		TRANSPARENT_FRAMEBUFFER,
		HOVERED,
		FOCUS_ON_SHOW,
		MOUSE_PASSTHROUGH,
		RED_BITS,
		GREEN_BITS,
		BLUE_BITS,
		ALPHA_BITS,
		DEPTH_BITS,
		STENCIL_BITS,
		ACCUM_RED_BITS,
		ACCUM_GREEN_BITS,
		ACCUM_BLUE_BITS,
		ACCUM_ALPHA_BITS,
		AUX_BUFFERS,
		STEREO,
		SAMPLES,
		SRGB_CAPABLE,
		REFRESH_RATE,
		DOUBLEBUFFER,
		CLIENT_API,
		CONTEXT_VERSION_MAJOR,
		CONTEXT_VERSION_MINOR,
		CONTEXT_REVISION,
		CONTEXT_ROBUSTNESS,
		OPENGL_FORWARD_COMPAT,
		CONTEXT_DEBUG,
		OPENGL_PROFILE,
		CONTEXT_RELEASE_BEHAVIOR,
		CONTEXT_NO_ERROR,
		CONTEXT_CREATION_API,
		SCALE_TO_MONITOR,
		COCOA_RETINA_FRAMEBUFFER,
		COCOA_FRAME_NAME,
		COCOA_GRAPHICS_SWITCHING,
		X11_CLASS_NAME,
		X11_INSTANCE_NAME,
		WIN32_KEYBOARD_MENU
	};
} // namespace assec