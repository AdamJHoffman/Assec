#include "acpch.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "GLFWWindowContext.h"
#include "GLFWWindow.h"
#include "GLFWInput.h"

#include "input/Input.h"

namespace assec::graphics
{
	GLFWWindowContext::GLFWWindowContext() : WindowContext::WindowContext() {}
	GLFWWindowContext::~GLFWWindowContext() {}
	void GLFWWindowContext::init(CONST_REF(InitHints) hints)
	{
		TIME_FUNCTION;
		glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, hints.joystickHatsAsButtons);
		glfwInitHint(GLFW_ANGLE_PLATFORM_TYPE, toGLFWType(hints.anglePlatformType));
		glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, hints.setCurrentDirectoyToResources);
		glfwInitHint(GLFW_COCOA_MENUBAR, hints.createBasicMenuBar);
		this->m_Initialized = glfwInit();
		if (this->m_Initialized)
		{
			glfwSetErrorCallback([](int error, const char* description)
				{
					std::string name = "";
					switch (error)
					{
					case GLFW_NO_ERROR:
						name = "NO ERROR";
						break;
					case GLFW_NOT_INITIALIZED:
						name = "GLFW_NOT_INITIALIZED";
						break;
					case GLFW_NO_CURRENT_CONTEXT:
						name = "NO_CURRENT_CONTEXT";
						break;
					case GLFW_INVALID_ENUM:
						name = "INVALID_ENUM";
						break;
					case GLFW_INVALID_VALUE:
						name = "INVALID_VALUE";
						break;
					case GLFW_OUT_OF_MEMORY:
						name = "OUT_OF_MEMORY";
						break;
					case GLFW_API_UNAVAILABLE:
						name = "API_UNAVAILABLE";
						break;
					case GLFW_VERSION_UNAVAILABLE:
						name = "VERSION_UNAVAILABLE";
						break;
					case GLFW_PLATFORM_ERROR:
						name = "PLATFORM_ERROR";
						break;
					case GLFW_FORMAT_UNAVAILABLE:
						name = "FORMAT_UNAVAILABLE";
						break;
					case GLFW_NO_WINDOW_CONTEXT:
						name = "NO_WINDOW_CONTEXT";
						break;
					case GLFW_CURSOR_UNAVAILABLE:
						name = "CURSOR_UNAVAILABLE";
						break;
					case GLFW_FEATURE_UNAVAILABLE:
						name = "FEATURE_UNAVAILABLE";
						break;
					case GLFW_FEATURE_UNIMPLEMENTED:
						name = "FEATURE_UNIMPLEMENTED";
						break;
					}
					std::string message = std::string("[ ") + name + std::string(" ] with message: ") + std::string(description);
					AC_CORE_ASSERT(!error, (message));
				});
			glfwSetJoystickCallback([](int id, int action) 
				{
					switch (action)
					{
					case GLFW_CONNECTED:
						input::Input::onJoyStickConnected(makeRef<input::GLFWJoystick>(id));
						break;
					case GLFW_DISCONNECTED:
						input::Input::onJoyStickDisconnected(joystickIDFromGLFWType(id));
						break;
					}
				});
		}
	}
	void GLFWWindowContext::terminate()
	{
		TIME_FUNCTION;
		glfwTerminate();
	}
	glm::vec3 GLFWWindowContext::getVersion() const
	{
		TIME_FUNCTION;
		int major = 0, minor = 0, revision = 0;
		glfwGetVersion(&major, &minor, &revision);
		return glm::vec3{major, minor, revision};
	}
	std::string GLFWWindowContext::getVersionAsString() const
	{
		TIME_FUNCTION;
		return std::string(glfwGetVersionString());
	}
	std::pair<uint32_t, std::string> GLFWWindowContext::getError() const
	{
		TIME_FUNCTION;
		const char* description;
		int code = glfwGetError(&description);
		return std::make_pair(static_cast<uint32_t>(code), std::string(description));
	}

	const std::vector<scope<Monitor>> GLFWWindowContext::getMonitors() const
	{
		TIME_FUNCTION;
		std::vector<scope<Monitor>> result = std::vector<scope<Monitor>>();
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		for (int i = 0; i < count; i++)
		{
			result.push_back(std::make_unique<GLFWMonitor>(monitors[i]));
		}
		return result;
	}
	const scope<Monitor> GLFWWindowContext::getPrimaryMonitor() const
	{
		TIME_FUNCTION;
		return std::make_unique<GLFWMonitor>(glfwGetPrimaryMonitor());
	}

	ref<Window> GLFWWindowContext::createWindow(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height,
		CONST_REF(std::string) title, const Monitor* monitor, const Window* share,
		CONST_REF(EventCallBackFn) eventCallBack) const
	{
		TIME_FUNCTION;
		return std::make_shared<GLFWWindow>(width, height, title, monitor, share, eventCallBack);
	}

	void GLFWWindowContext::pollEvents() const 
	{
		TIME_FUNCTION;
		glfwPollEvents();
	}
	void GLFWWindowContext::waitEvents() const
	{
		TIME_FUNCTION;
		glfwWaitEvents();
	}
	void GLFWWindowContext::waitEventsTimeout(double timeout) const
	{
		TIME_FUNCTION;
		glfwWaitEventsTimeout(timeout);
	}
	void GLFWWindowContext::postEmptyEvent() const
	{
		TIME_FUNCTION;
		glfwPostEmptyEvent();
	}

	bool GLFWWindowContext::isRawMouseMotionSupported() const
	{
		TIME_FUNCTION;
		return glfwRawMouseMotionSupported();
	}

	std::string GLFWWindowContext::getKeyName(CONST_REF(KEY) key) const
	{
		TIME_FUNCTION;
		return std::string(glfwGetKeyName(toGLFWType(key), this->getKeyScancode(key)));
	}
	uint32_t GLFWWindowContext::getKeyScancode(CONST_REF(KEY) key) const
	{
		TIME_FUNCTION;
		return static_cast<uint32_t>(glfwGetKeyScancode(toGLFWType(key)));
	}

	//virtual cursor createCursor(cursorhints)
	//virtual cursor createStandardCursor(cursorhints)
	void GLFWWindowContext::destroyCursor(CONST_REF(Cursor) cursor) const
	{
		TIME_FUNCTION;
		glfwDestroyCursor((GLFWcursor*)cursor.nativeCursor);
	}

	bool GLFWWindowContext::isJoystickPresent(CONST_REF(JoystickID) id) const
	{
		TIME_FUNCTION;
		return glfwJoystickPresent(toGLFWType(id));
	}
	void GLFWWindowContext::updateGamepadMappings(CONST_REF(std::string) mapping) const
	{
		TIME_FUNCTION;
		glfwUpdateGamepadMappings(mapping.c_str());
	}

	double GLFWWindowContext::getCurrentTime() const
	{
		TIME_FUNCTION;
		return glfwGetTime();
	}
	void GLFWWindowContext::setCurrentTime(double time) const
	{
		TIME_FUNCTION;
		glfwSetTime(time);
	}
	uint64_t GLFWWindowContext::getTimerValue() const
	{
		TIME_FUNCTION;
		return glfwGetTimerValue();
	}
	uint64_t GLFWWindowContext::getTimerFrequency() const
	{
		TIME_FUNCTION;
		return glfwGetTimerFrequency();
	}

	CONST_REF(Window) GLFWWindowContext::getCurrentContext() const
	{
		TIME_FUNCTION;
		return *((GLFWWindow*)glfwGetWindowUserPointer(glfwGetCurrentContext()));
	}

	bool GLFWWindowContext::isExtensionSupported(CONST_REF(std::string) extension) const
	{
		TIME_FUNCTION;
		return glfwExtensionSupported(extension.c_str());
	}


	const uint32_t toGLFWType(CONST_REF(KEY) key)
	{
		TIME_FUNCTION;
		switch (key)
		{
		case KEY::KEY_UNKNOWN:
			return GLFW_KEY_UNKNOWN;
			break;
		case KEY::KEY_SPACE:
			return GLFW_KEY_SPACE;
			break;
		case KEY::KEY_APOSTROPHE:
			return GLFW_KEY_APOSTROPHE;
			break;
		case KEY::KEY_COMMA:
			return GLFW_KEY_COMMA;
			break;
		case KEY::KEY_MINUS:
			return GLFW_KEY_MINUS;
			break;
		case KEY::KEY_PERIOD:
			return GLFW_KEY_PERIOD;
			break;
		case KEY::KEY_SLASH:
			return GLFW_KEY_SLASH;
			break;
		case KEY::KEY_0:
			return GLFW_KEY_0;
			break;
		case KEY::KEY_1:
			return GLFW_KEY_1;
			break;
		case KEY::KEY_2:
			return GLFW_KEY_2;
			break;
		case KEY::KEY_3:
			return GLFW_KEY_3;
			break;
		case KEY::KEY_4:
			return GLFW_KEY_4;
			break;
		case KEY::KEY_5:
			return GLFW_KEY_5;
			break;
		case KEY::KEY_6:
			return GLFW_KEY_6;
			break;
		case KEY::KEY_7:
			return GLFW_KEY_7;
			break;
		case KEY::KEY_8:
			return GLFW_KEY_8;
			break;
		case KEY::KEY_9:
			return GLFW_KEY_9;
			break;
		case KEY::KEY_SEMICOLON:
			return GLFW_KEY_SEMICOLON;
			break;
		case KEY::KEY_EQUAL:
			return GLFW_KEY_EQUAL;
			break;
		case KEY::KEY_A:
			return GLFW_KEY_A;
			break;
		case KEY::KEY_B:
			return GLFW_KEY_B;
			break;
		case KEY::KEY_C:
			return GLFW_KEY_C;
			break;
		case KEY::KEY_D:
			return GLFW_KEY_D;
			break;
		case KEY::KEY_E:
			return GLFW_KEY_E;
			break;
		case KEY::KEY_F:
			return GLFW_KEY_F;
			break;
		case KEY::KEY_G:
			return GLFW_KEY_G;
			break;
		case KEY::KEY_H:
			return GLFW_KEY_H;
			break;
		case KEY::KEY_I:
			return GLFW_KEY_I;
			break;
		case KEY::KEY_J:
			return GLFW_KEY_J;
			break;
		case KEY::KEY_K:
			return GLFW_KEY_K;
			break;
		case KEY::KEY_L:
			return GLFW_KEY_L;
			break;
		case KEY::KEY_M:
			return GLFW_KEY_M;
			break;
		case KEY::KEY_N:
			return GLFW_KEY_N;
			break;
		case KEY::KEY_O:
			return GLFW_KEY_O;
			break;
		case KEY::KEY_P:
			return GLFW_KEY_P;
			break;
		case KEY::KEY_Q:
			return GLFW_KEY_Q;
			break;
		case KEY::KEY_R:
			return GLFW_KEY_R;
			break;
		case KEY::KEY_S:
			return GLFW_KEY_S;
			break;
		case KEY::KEY_T:
			return GLFW_KEY_T;
			break;
		case KEY::KEY_U:
			return GLFW_KEY_U;
			break;
		case KEY::KEY_V:
			return GLFW_KEY_V;
			break;
		case KEY::KEY_W:
			return GLFW_KEY_W;
			break;
		case KEY::KEY_X:
			return GLFW_KEY_X;
			break;
		case KEY::KEY_Y:
			return GLFW_KEY_Y;
			break;
		case KEY::KEY_Z:
			return GLFW_KEY_Z;
			break;
		case KEY::KEY_LEFT_BRACKET:
			return GLFW_KEY_LEFT_BRACKET;
			break;
		case KEY::KEY_BACKSLASH:
			return GLFW_KEY_BACKSLASH;
			break;
		case KEY::KEY_RIGHT_BRACKET:
			return GLFW_KEY_RIGHT_BRACKET;
			break;
		case KEY::KEY_GRAVE_ACCENT:
			return GLFW_KEY_GRAVE_ACCENT;
			break;
		case KEY::KEY_WORLD_1:
			return GLFW_KEY_WORLD_1;
			break;
		case KEY::KEY_WORLD_2:
			return GLFW_KEY_WORLD_2;
			break;
		case KEY::KEY_ESCAPE:
			return GLFW_KEY_ESCAPE;
			break;
		case KEY::KEY_ENTER:
			return GLFW_KEY_ENTER;
			break;
		case KEY::KEY_TAB:
			return GLFW_KEY_TAB;
			break;
		case KEY::KEY_BACKSPACE:
			return GLFW_KEY_BACKSPACE;
			break;
		case KEY::KEY_INSERT:
			return GLFW_KEY_INSERT;
			break;
		case KEY::KEY_DELETE:
			return GLFW_KEY_DELETE;
			break;
		case KEY::KEY_RIGHT:
			return GLFW_KEY_RIGHT;
			break;
		case KEY::KEY_LEFT:
			return GLFW_KEY_LEFT;
			break;
		case KEY::KEY_DOWN:
			return GLFW_KEY_DOWN;
			break;
		case KEY::KEY_UP:
			return GLFW_KEY_UP;
			break;
		case KEY::KEY_PAGE_UP:
			return GLFW_KEY_PAGE_UP;
			break;
		case KEY::KEY_PAGE_DOWN:
			return GLFW_KEY_PAGE_DOWN;
			break;
		case KEY::KEY_HOME:
			return GLFW_KEY_HOME;
			break;
		case KEY::KEY_END:
			return GLFW_KEY_END;
			break;
		case KEY::KEY_CAPS_LOCK:
			return GLFW_KEY_CAPS_LOCK;
			break;
		case KEY::KEY_SCROLL_LOCK:
			return GLFW_KEY_SCROLL_LOCK;
			break;
		case KEY::KEY_NUM_LOCK:
			return GLFW_KEY_NUM_LOCK;
			break;
		case KEY::KEY_PRINT_SCREEN:
			return GLFW_KEY_PRINT_SCREEN;
			break;
		case KEY::KEY_PAUSE:
			return GLFW_KEY_PAUSE;
			break;
		case KEY::KEY_F1:
			return GLFW_KEY_F1;
			break;
		case KEY::KEY_F2:
			return GLFW_KEY_F2;
			break;
		case KEY::KEY_F3:
			return GLFW_KEY_F3;
			break;
		case KEY::KEY_F4:
			return GLFW_KEY_F4;
			break;
		case KEY::KEY_F5:
			return GLFW_KEY_F5;
			break;
		case KEY::KEY_F6:
			return GLFW_KEY_F6;
			break;
		case KEY::KEY_F7:
			return GLFW_KEY_F7;
			break;
		case KEY::KEY_F8:
			return GLFW_KEY_F8;
			break;
		case KEY::KEY_F9:
			return GLFW_KEY_F9;
			break;
		case KEY::KEY_F10:
			return GLFW_KEY_F10;
			break;
		case KEY::KEY_F11:
			return GLFW_KEY_F11;
			break;
		case KEY::KEY_F12:
			return GLFW_KEY_F12;
			break;
		case KEY::KEY_F13:
			return GLFW_KEY_F13;
			break;
		case KEY::KEY_F14:
			return GLFW_KEY_F14;
			break;
		case KEY::KEY_F15:
			return GLFW_KEY_F15;
			break;
		case KEY::KEY_F16:
			return GLFW_KEY_F16;
			break;
		case KEY::KEY_F17:
			return GLFW_KEY_F17;
			break;
		case KEY::KEY_F18:
			return GLFW_KEY_F18;
			break;
		case KEY::KEY_F19:
			return GLFW_KEY_F19;
			break;
		case KEY::KEY_F20:
			return GLFW_KEY_F20;
			break;
		case KEY::KEY_F21:
			return GLFW_KEY_F21;
			break;
		case KEY::KEY_F22:
			return GLFW_KEY_F22;
			break;
		case KEY::KEY_F23:
			return GLFW_KEY_F23;
			break;
		case KEY::KEY_F24:
			return GLFW_KEY_F24;
			break;
		case KEY::KEY_F25:
			return GLFW_KEY_F25;
			break;
		case KEY::KEY_KP_0:
			return GLFW_KEY_KP_0;
			break;
		case KEY::KEY_KP_1:
			return GLFW_KEY_KP_1;
			break;
		case KEY::KEY_KP_2:
			return GLFW_KEY_KP_2;
			break;
		case KEY::KEY_KP_3:
			return GLFW_KEY_KP_3;
			break;
		case KEY::KEY_KP_4:
			return GLFW_KEY_KP_4;
			break;
		case KEY::KEY_KP_5:
			return GLFW_KEY_KP_5;
			break;
		case KEY::KEY_KP_6:
			return GLFW_KEY_KP_6;
			break;
		case KEY::KEY_KP_7:
			return GLFW_KEY_KP_7;
			break;
		case KEY::KEY_KP_8:
			return GLFW_KEY_KP_8;
			break;
		case KEY::KEY_KP_9:
			return GLFW_KEY_KP_9;
			break;
		case KEY::KEY_KP_DECIMAL:
			return GLFW_KEY_KP_DECIMAL;
			break;
		case KEY::KEY_KP_DIVIDE:
			return GLFW_KEY_KP_DIVIDE;
			break;
		case KEY::KEY_KP_MULTIPLY:
			return GLFW_KEY_KP_MULTIPLY;
			break;
		case KEY::KEY_KP_SUBTRACT:
			return GLFW_KEY_KP_SUBTRACT;
			break;
		case KEY::KEY_KP_ADD:
			return GLFW_KEY_KP_ADD;
			break;
		case KEY::KEY_KP_ENTER:
			return GLFW_KEY_KP_ENTER;
			break;
		case KEY::KEY_KP_EQUAL:
			return GLFW_KEY_KP_EQUAL;
			break;
		case KEY::KEY_LEFT_SHIFT:
			return GLFW_KEY_LEFT_SHIFT;
			break;
		case KEY::KEY_LEFT_CONTROL:
			return GLFW_KEY_LEFT_CONTROL;
			break;
		case KEY::KEY_LEFT_ALT:
			return GLFW_KEY_LEFT_ALT;
			break;
		case KEY::KEY_LEFT_SUPER:
			return GLFW_KEY_LEFT_SUPER;
			break;
		case KEY::KEY_RIGHT_SHIFT:
			return GLFW_KEY_RIGHT_SHIFT;
			break;
		case KEY::KEY_RIGHT_CONTROL:
			return GLFW_KEY_RIGHT_CONTROL;
			break;
		case KEY::KEY_RIGHT_ALT:
			return GLFW_KEY_RIGHT_ALT;
			break;
		case KEY::KEY_RIGHT_SUPER:
			return GLFW_KEY_RIGHT_SUPER;
			break;
		case KEY::KEY_MENU:
			return GLFW_KEY_MENU;
			break;
		default:
			return GLFW_KEY_UNKNOWN;
			break;
		}
	}

	const uint32_t toGLFWType(CONST_REF(MOUSE) key)
	{
		TIME_FUNCTION;
		switch (key) {
		case MOUSE::MOUSE_BUTTON_LEFT:
			return GLFW_MOUSE_BUTTON_LEFT;
			break;
		case MOUSE::MOUSE_BUTTON_RIGHT:
			return GLFW_MOUSE_BUTTON_RIGHT;
			break;
		case MOUSE::MOUSE_BUTTON_MIDDLE:
			return GLFW_MOUSE_BUTTON_MIDDLE;
			break;
		case MOUSE::MOUSE_BUTTON_4:
			return GLFW_MOUSE_BUTTON_4;
			break;
		case MOUSE::MOUSE_BUTTON_5:
			return GLFW_MOUSE_BUTTON_5;
			break;
		case MOUSE::MOUSE_BUTTON_6:
			return GLFW_MOUSE_BUTTON_6;
			break;
		case MOUSE::MOUSE_BUTTON_7:
			return GLFW_MOUSE_BUTTON_7;
			break;
		case MOUSE::MOUSE_BUTTON_8:
			return GLFW_MOUSE_BUTTON_8;
			break;
		default:
			return GLFW_MOUSE_BUTTON_LEFT;
			break;
		}
	}

	const uint32_t toGLFWType(CONST_REF(AnglePlatformType) anglePlatformType)
	{
		TIME_FUNCTION;
		switch (anglePlatformType) {
		case AnglePlatformType::OPENGL:
			return GLFW_ANGLE_PLATFORM_TYPE_OPENGL;
			break;
		case AnglePlatformType::OPENGLES:
			return GLFW_ANGLE_PLATFORM_TYPE_OPENGLES;
			break;
		case AnglePlatformType::D3D9:
			return GLFW_ANGLE_PLATFORM_TYPE_D3D9;
			break;
		case AnglePlatformType::D3D11:
			return GLFW_ANGLE_PLATFORM_TYPE_D3D11;
			break;
		case AnglePlatformType::VULKAN:
			return GLFW_ANGLE_PLATFORM_TYPE_VULKAN;
			break;
		case AnglePlatformType::METAL:
			return GLFW_ANGLE_PLATFORM_TYPE_METAL;
			break;
		default:
			return GLFW_ANGLE_PLATFORM_TYPE_NONE;
			break;
		}
	}

	const uint32_t toGLFWType(CONST_REF(WindowAttribute) windowAttribute)
	{
		TIME_FUNCTION;
		switch (windowAttribute)
		{
		case WindowAttribute::FOCUSED:
			return GLFW_FOCUSED;
			break;
		case WindowAttribute::ICONIFIED:
			return GLFW_ICONIFIED;
			break;
		case WindowAttribute::RESIZABLE:
			return GLFW_RESIZABLE;
			break;
		case WindowAttribute::VISIBLE:
			return GLFW_VISIBLE;
			break;
		case WindowAttribute::DECORATED:
			return GLFW_DECORATED;
			break;
		case WindowAttribute::AUTO_ICONIFY:
			return GLFW_AUTO_ICONIFY;
			break;
		case WindowAttribute::FLOATING:
			return GLFW_FLOATING;
			break;
		case WindowAttribute::MAXIMIZED:
			return GLFW_MAXIMIZED;
			break;
		case WindowAttribute::CENTER_CURSOR:
			return GLFW_CENTER_CURSOR;
			break;
		case WindowAttribute::TRANSPARENT_FRAMEBUFFER:
			return GLFW_TRANSPARENT_FRAMEBUFFER;
			break;
		case WindowAttribute::HOVERED:
			return GLFW_HOVERED;
			break;
		case WindowAttribute::FOCUS_ON_SHOW:
			return GLFW_FOCUS_ON_SHOW;
			break;
		case WindowAttribute::MOUSE_PASSTHROUGH:
			return GLFW_MOUSE_PASSTHROUGH;
			break;
		case WindowAttribute::RED_BITS:
			return GLFW_RED_BITS;
			break;
		case WindowAttribute::GREEN_BITS:
			return GLFW_GREEN_BITS;
			break;
		case WindowAttribute::BLUE_BITS:
			return GLFW_BLUE_BITS;
			break;
		case WindowAttribute::ALPHA_BITS:
			return GLFW_ALPHA_BITS;
			break;
		case WindowAttribute::DEPTH_BITS:
			return GLFW_DEPTH_BITS;
			break;
		case WindowAttribute::STENCIL_BITS:
			return GLFW_STENCIL_BITS;
			break;
		case WindowAttribute::ACCUM_RED_BITS:
			return GLFW_ACCUM_RED_BITS;
			break;
		case WindowAttribute::ACCUM_GREEN_BITS:
			return GLFW_ACCUM_GREEN_BITS;
			break;
		case WindowAttribute::ACCUM_BLUE_BITS:
			return GLFW_ACCUM_BLUE_BITS;
			break;
		case WindowAttribute::ACCUM_ALPHA_BITS:
			return GLFW_ACCUM_ALPHA_BITS;
			break;
		case WindowAttribute::AUX_BUFFERS:
			return GLFW_AUX_BUFFERS;
			break;
		case WindowAttribute::STEREO:
			return GLFW_STEREO;
			break;
		case WindowAttribute::SAMPLES:
			return GLFW_SAMPLES;
			break;
		case WindowAttribute::SRGB_CAPABLE:
			return GLFW_SRGB_CAPABLE;
			break;
		case WindowAttribute::REFRESH_RATE:
			return GLFW_REFRESH_RATE;
			break;
		case WindowAttribute::DOUBLEBUFFER:
			return GLFW_DOUBLEBUFFER;
			break;
		case WindowAttribute::CLIENT_API:
			return GLFW_CLIENT_API;
			break;
		case WindowAttribute::CONTEXT_VERSION_MAJOR:
			return GLFW_CONTEXT_VERSION_MAJOR;
			break;
		case WindowAttribute::CONTEXT_VERSION_MINOR:
			return GLFW_CONTEXT_VERSION_MINOR;
			break;
		case WindowAttribute::CONTEXT_REVISION:
			return GLFW_CONTEXT_REVISION;
			break;
		case WindowAttribute::CONTEXT_ROBUSTNESS:
			return GLFW_CONTEXT_ROBUSTNESS;
			break;
		case WindowAttribute::OPENGL_FORWARD_COMPAT:
			return GLFW_OPENGL_FORWARD_COMPAT;
			break;
		case WindowAttribute::CONTEXT_DEBUG:
			return GLFW_CONTEXT_DEBUG;
			break;
		case WindowAttribute::OPENGL_PROFILE:
			return GLFW_OPENGL_PROFILE;
			break;
		case WindowAttribute::CONTEXT_RELEASE_BEHAVIOR:
			return GLFW_CONTEXT_RELEASE_BEHAVIOR;
			break;
		case WindowAttribute::CONTEXT_NO_ERROR:
			return GLFW_CONTEXT_NO_ERROR;
			break;
		case WindowAttribute::CONTEXT_CREATION_API:
			return GLFW_CONTEXT_CREATION_API;
			break;
		case WindowAttribute::SCALE_TO_MONITOR:
			return GLFW_SCALE_TO_MONITOR;
			break;
		case WindowAttribute::COCOA_RETINA_FRAMEBUFFER:
			return GLFW_COCOA_RETINA_FRAMEBUFFER;
			break;
		case WindowAttribute::COCOA_FRAME_NAME:
			return GLFW_COCOA_FRAME_NAME;
			break;
		case WindowAttribute::COCOA_GRAPHICS_SWITCHING:
			return GLFW_COCOA_GRAPHICS_SWITCHING;
			break;
		case WindowAttribute::X11_CLASS_NAME:
			return GLFW_X11_CLASS_NAME;
			break;
		case WindowAttribute::X11_INSTANCE_NAME:
			return GLFW_X11_INSTANCE_NAME;
			break;
		case WindowAttribute::WIN32_KEYBOARD_MENU:
			return GLFW_WIN32_KEYBOARD_MENU;
			break;
		default:
			return 0;
			break;
		}
	}

	const uint32_t toGLFWType(CONST_REF(CursorMode) mode)
	{
		TIME_FUNCTION;
		switch (mode)
		{
		case CursorMode::HIDDEN:
			return GLFW_CURSOR_HIDDEN;
			break;
		case CursorMode::DISABLED:
			return GLFW_CURSOR_DISABLED;
			break;
		default:
			return GLFW_CURSOR_NORMAL;
			break;
		}
	}

	const uint32_t toGLFWType(CONST_REF(JoystickID) id)
	{
		TIME_FUNCTION;
		switch (id)
		{
			case JoystickID::JOYSTICK_2:
				return GLFW_JOYSTICK_2;
				break;
			case JoystickID::JOYSTICK_3:
				return GLFW_JOYSTICK_3;
				break;
			case JoystickID::JOYSTICK_4:
				return GLFW_JOYSTICK_4;
				break;
			case JoystickID::JOYSTICK_5:
				return GLFW_JOYSTICK_5;
				break;
			case JoystickID::JOYSTICK_6:
				return GLFW_JOYSTICK_6;
				break;
			case JoystickID::JOYSTICK_7:
				return GLFW_JOYSTICK_7;
				break;
			case JoystickID::JOYSTICK_8:
				return GLFW_JOYSTICK_8;
				break;
			case JoystickID::JOYSTICK_9:
				return GLFW_JOYSTICK_9;
				break;
			case JoystickID::JOYSTICK_10:
				return GLFW_JOYSTICK_10;
				break;
			case JoystickID::JOYSTICK_11:
				return GLFW_JOYSTICK_11;
				break;
			case JoystickID::JOYSTICK_12:
				return GLFW_JOYSTICK_12;
				break;
			case JoystickID::JOYSTICK_13:
				return GLFW_JOYSTICK_13;
				break;
			case JoystickID::JOYSTICK_14:
				return GLFW_JOYSTICK_14;
				break;
			case JoystickID::JOYSTICK_15:
				return GLFW_JOYSTICK_15;
				break;
			case JoystickID::JOYSTICK_16:
				return GLFW_JOYSTICK_16;
				break;
			default:
				return GLFW_JOYSTICK_1;
				break;
		}
	}

	const KEY keyFromGLFWType(CONST_REF(int) key)
	{
		TIME_FUNCTION;
		switch (key)
		{
		case GLFW_KEY_UNKNOWN:
			return KEY::KEY_UNKNOWN;
			break;
		case GLFW_KEY_SPACE:
			return KEY::KEY_SPACE;
			break;
		case GLFW_KEY_APOSTROPHE:
			return KEY::KEY_APOSTROPHE;
			break;
		case GLFW_KEY_COMMA:
			return KEY::KEY_COMMA;
			break;
		case GLFW_KEY_MINUS:
			return KEY::KEY_MINUS;
			break;
		case GLFW_KEY_PERIOD:
			return KEY::KEY_PERIOD;
			break;
		case GLFW_KEY_SLASH:
			return KEY::KEY_SLASH;
			break;
		case GLFW_KEY_0:
			return KEY::KEY_0;
			break;
		case GLFW_KEY_1:
			return KEY::KEY_1;
			break;
		case GLFW_KEY_2:
			return KEY::KEY_2;
			break;
		case GLFW_KEY_3:
			return KEY::KEY_3;
			break;
		case GLFW_KEY_4:
			return KEY::KEY_4;
			break;
		case GLFW_KEY_5:
			return KEY::KEY_5;
			break;
		case GLFW_KEY_6:
			return KEY::KEY_6;
			break;
		case GLFW_KEY_7:
			return KEY::KEY_7;
			break;
		case GLFW_KEY_8:
			return KEY::KEY_8;
			break;
		case GLFW_KEY_9:
			return KEY::KEY_9;
			break;
		case GLFW_KEY_SEMICOLON:
			return KEY::KEY_SEMICOLON;
			break;
		case GLFW_KEY_EQUAL:
			return KEY::KEY_EQUAL;
			break;
		case GLFW_KEY_A:
			return KEY::KEY_A;
			break;
		case GLFW_KEY_B:
			return KEY::KEY_B;
			break;
		case GLFW_KEY_C:
			return KEY::KEY_C;
			break;
		case GLFW_KEY_D:
			return KEY::KEY_D;
			break;
		case GLFW_KEY_E:
			return KEY::KEY_E;
			break;
		case GLFW_KEY_F:
			return KEY::KEY_F;
			break;
		case GLFW_KEY_G:
			return KEY::KEY_G;
			break;
		case GLFW_KEY_H:
			return KEY::KEY_H;
			break;
		case GLFW_KEY_I:
			return KEY::KEY_I;
			break;
		case GLFW_KEY_J:
			return KEY::KEY_J;
			break;
		case GLFW_KEY_K:
			return KEY::KEY_K;
			break;
		case GLFW_KEY_L:
			return KEY::KEY_L;
			break;
		case GLFW_KEY_M:
			return KEY::KEY_M;
			break;
		case GLFW_KEY_N:
			return KEY::KEY_N;
			break;
		case GLFW_KEY_O:
			return KEY::KEY_O;
			break;
		case GLFW_KEY_P:
			return KEY::KEY_P;
			break;
		case GLFW_KEY_Q:
			return KEY::KEY_Q;
			break;
		case GLFW_KEY_R:
			return KEY::KEY_R;
			break;
		case GLFW_KEY_S:
			return KEY::KEY_S;
			break;
		case GLFW_KEY_T:
			return KEY::KEY_T;
			break;
		case GLFW_KEY_U:
			return KEY::KEY_U;
			break;
		case GLFW_KEY_V:
			return KEY::KEY_V;
			break;
		case GLFW_KEY_W:
			return KEY::KEY_W;
			break;
		case GLFW_KEY_X:
			return KEY::KEY_X;
			break;
		case GLFW_KEY_Y:
			return KEY::KEY_Y;
			break;
		case GLFW_KEY_Z:
			return KEY::KEY_Z;
			break;
		case GLFW_KEY_LEFT_BRACKET:
			return KEY::KEY_LEFT_BRACKET;
			break;
		case GLFW_KEY_BACKSLASH:
			return KEY::KEY_BACKSLASH;
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			return KEY::KEY_RIGHT_BRACKET;
			break;
		case GLFW_KEY_GRAVE_ACCENT:
			return KEY::KEY_GRAVE_ACCENT;
			break;
		case GLFW_KEY_WORLD_1:
			return KEY::KEY_WORLD_1;
			break;
		case GLFW_KEY_WORLD_2:
			return KEY::KEY_WORLD_2;
			break;
		case GLFW_KEY_ESCAPE:
			return KEY::KEY_ESCAPE;
			break;
		case GLFW_KEY_ENTER:
			return KEY::KEY_ENTER;
			break;
		case GLFW_KEY_TAB:
			return KEY::KEY_TAB;
			break;
		case GLFW_KEY_BACKSPACE:
			return KEY::KEY_BACKSPACE;
			break;
		case GLFW_KEY_INSERT:
			return KEY::KEY_INSERT;
			break;
		case GLFW_KEY_DELETE:
			return KEY::KEY_DELETE;
			break;
		case GLFW_KEY_RIGHT:
			return KEY::KEY_RIGHT;
			break;
		case GLFW_KEY_LEFT:
			return KEY::KEY_LEFT;
			break;
		case GLFW_KEY_DOWN:
			return KEY::KEY_DOWN;
			break;
		case GLFW_KEY_UP:
			return KEY::KEY_UP;
			break;
		case GLFW_KEY_PAGE_UP:
			return KEY::KEY_PAGE_UP;
			break;
		case GLFW_KEY_PAGE_DOWN:
			return KEY::KEY_PAGE_DOWN;
			break;
		case GLFW_KEY_HOME:
			return KEY::KEY_HOME;
			break;
		case GLFW_KEY_END:
			return KEY::KEY_END;
			break;
		case GLFW_KEY_CAPS_LOCK:
			return KEY::KEY_CAPS_LOCK;
			break;
		case GLFW_KEY_SCROLL_LOCK:
			return KEY::KEY_SCROLL_LOCK;
			break;
		case GLFW_KEY_NUM_LOCK:
			return KEY::KEY_NUM_LOCK;
			break;
		case GLFW_KEY_PRINT_SCREEN:
			return KEY::KEY_PRINT_SCREEN;
			break;
		case GLFW_KEY_PAUSE:
			return KEY::KEY_PAUSE;
			break;
		case GLFW_KEY_F1:
			return KEY::KEY_F1;
			break;
		case GLFW_KEY_F2:
			return KEY::KEY_F2;
			break;
		case GLFW_KEY_F3:
			return KEY::KEY_F3;
			break;
		case GLFW_KEY_F4:
			return KEY::KEY_F4;
			break;
		case GLFW_KEY_F5:
			return KEY::KEY_F5;
			break;
		case GLFW_KEY_F6:
			return KEY::KEY_F6;
			break;
		case GLFW_KEY_F7:
			return KEY::KEY_F7;
			break;
		case GLFW_KEY_F8:
			return KEY::KEY_F8;
			break;
		case GLFW_KEY_F9:
			return KEY::KEY_F9;
			break;
		case GLFW_KEY_F10:
			return KEY::KEY_F10;
			break;
		case GLFW_KEY_F11:
			return KEY::KEY_F11;
			break;
		case GLFW_KEY_F12:
			return KEY::KEY_F12;
			break;
		case GLFW_KEY_F13:
			return KEY::KEY_F13;
			break;
		case GLFW_KEY_F14:
			return KEY::KEY_F14;
			break;
		case GLFW_KEY_F15:
			return KEY::KEY_F15;
			break;
		case GLFW_KEY_F16:
			return KEY::KEY_F16;
			break;
		case GLFW_KEY_F17:
			return KEY::KEY_F17;
			break;
		case GLFW_KEY_F18:
			return KEY::KEY_F18;
			break;
		case GLFW_KEY_F19:
			return KEY::KEY_F19;
			break;
		case GLFW_KEY_F20:
			return KEY::KEY_F20;
			break;
		case GLFW_KEY_F21:
			return KEY::KEY_F21;
			break;
		case GLFW_KEY_F22:
			return KEY::KEY_F22;
			break;
		case GLFW_KEY_F23:
			return KEY::KEY_F23;
			break;
		case GLFW_KEY_F24:
			return KEY::KEY_F24;
			break;
		case GLFW_KEY_F25:
			return KEY::KEY_F25;
			break;
		case GLFW_KEY_KP_0:
			return KEY::KEY_KP_0;
			break;
		case GLFW_KEY_KP_1:
			return KEY::KEY_KP_1;
			break;
		case GLFW_KEY_KP_2:
			return KEY::KEY_KP_2;
			break;
		case GLFW_KEY_KP_3:
			return KEY::KEY_KP_3;
			break;
		case GLFW_KEY_KP_4:
			return KEY::KEY_KP_4;
			break;
		case GLFW_KEY_KP_5:
			return KEY::KEY_KP_5;
			break;
		case GLFW_KEY_KP_6:
			return KEY::KEY_KP_6;
			break;
		case GLFW_KEY_KP_7:
			return KEY::KEY_KP_7;
			break;
		case GLFW_KEY_KP_8:
			return KEY::KEY_KP_8;
			break;
		case GLFW_KEY_KP_9:
			return KEY::KEY_KP_9;
			break;
		case GLFW_KEY_KP_DECIMAL:
			return KEY::KEY_KP_DECIMAL;
			break;
		case GLFW_KEY_KP_DIVIDE:
			return KEY::KEY_KP_DIVIDE;
			break;
		case GLFW_KEY_KP_MULTIPLY:
			return KEY::KEY_KP_MULTIPLY;
			break;
		case GLFW_KEY_KP_SUBTRACT:
			return KEY::KEY_KP_SUBTRACT;
			break;
		case GLFW_KEY_KP_ADD:
			return KEY::KEY_KP_ADD;
			break;
		case GLFW_KEY_KP_ENTER:
			return KEY::KEY_KP_ENTER;
			break;
		case GLFW_KEY_KP_EQUAL:
			return KEY::KEY_KP_EQUAL;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			return KEY::KEY_LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			return KEY::KEY_LEFT_CONTROL;
			break;
		case GLFW_KEY_LEFT_ALT:
			return KEY::KEY_LEFT_ALT;
			break;
		case GLFW_KEY_LEFT_SUPER:
			return KEY::KEY_LEFT_SUPER;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			return KEY::KEY_RIGHT_SHIFT;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			return KEY::KEY_RIGHT_CONTROL;
			break;
		case GLFW_KEY_RIGHT_ALT:
			return KEY::KEY_RIGHT_ALT;
			break;
		case GLFW_KEY_RIGHT_SUPER:
			return KEY::KEY_RIGHT_SUPER;
			break;
		case GLFW_KEY_MENU:
			return KEY::KEY_MENU;
			break;
		default:
			return KEY::KEY_UNKNOWN;
			break;
		}
	}

	const MOUSE buttonFromGLFWType(CONST_REF(int) key)
	{
		TIME_FUNCTION;
		switch (key)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			return MOUSE::MOUSE_BUTTON_LEFT;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return MOUSE::MOUSE_BUTTON_RIGHT;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			return MOUSE::MOUSE_BUTTON_MIDDLE;
			break;
		case GLFW_MOUSE_BUTTON_4:
			return MOUSE::MOUSE_BUTTON_4;
			break;
		case GLFW_MOUSE_BUTTON_5:
			return MOUSE::MOUSE_BUTTON_5;
			break;
		case GLFW_MOUSE_BUTTON_6:
			return MOUSE::MOUSE_BUTTON_6;
			break;
		case GLFW_MOUSE_BUTTON_7:
			return MOUSE::MOUSE_BUTTON_7;
			break;
		case GLFW_MOUSE_BUTTON_8:
			return MOUSE::MOUSE_BUTTON_8;
			break;
		default:
			return MOUSE::MOUSE_BUTTON_UNKNOWN;
			break;
		}
	}

	const CursorMode cursorModeFromGLFWType(CONST_REF(int) mode)
	{
		TIME_FUNCTION;
		switch (mode)
		{
		case GLFW_CURSOR_HIDDEN:
			return CursorMode::HIDDEN;
			break;
		case GLFW_CURSOR_DISABLED:
			return CursorMode::DISABLED;
			break;
		default:
			return CursorMode::NORMAL;
			break;
		}
	}

	const JoystickID joystickIDFromGLFWType(CONST_REF(int) id)
	{
		switch (id)
		{
		case GLFW_JOYSTICK_2:
			return JoystickID::JOYSTICK_2;
			break;
		case GLFW_JOYSTICK_3:
			return JoystickID::JOYSTICK_3;
			break;
		case GLFW_JOYSTICK_4:
			return JoystickID::JOYSTICK_4;
			break;
		case GLFW_JOYSTICK_5:
			return JoystickID::JOYSTICK_5;
			break;
		case GLFW_JOYSTICK_6:
			return JoystickID::JOYSTICK_6;
			break;
		case GLFW_JOYSTICK_7:
			return JoystickID::JOYSTICK_7;
			break;
		case GLFW_JOYSTICK_8:
			return JoystickID::JOYSTICK_8;
			break;
		case GLFW_JOYSTICK_9:
			return JoystickID::JOYSTICK_9;
			break;
		case GLFW_JOYSTICK_10:
			return JoystickID::JOYSTICK_10;
			break;
		case GLFW_JOYSTICK_11:
			return JoystickID::JOYSTICK_11;
			break;
		case GLFW_JOYSTICK_12:
			return JoystickID::JOYSTICK_12;
			break;
		case GLFW_JOYSTICK_13:
			return JoystickID::JOYSTICK_13;
			break;
		case GLFW_JOYSTICK_14:
			return JoystickID::JOYSTICK_14;
			break;
		case GLFW_JOYSTICK_15:
			return JoystickID::JOYSTICK_15;
			break;
		case GLFW_JOYSTICK_16:
			return JoystickID::JOYSTICK_16;
			break;
		default:
			return JoystickID::JOYSTICK_1;
			break;
		}
	}

} // namespace assec::graphics
