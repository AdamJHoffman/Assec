#include "acpch.h"

#include "GLFWWindowContext.h"

#include <GLFW/glfw3.h>

#include "GLFWWindow.h"

namespace assec::graphics
{
	GLFWWindowContext::GLFWWindowContext() : WindowContext::WindowContext() {}
	GLFWWindowContext::~GLFWWindowContext() {}
	void GLFWWindowContext::cleanup() const
	{
		TIME_FUNCTION;
		glfwTerminate();
	}
	const float GLFWWindowContext::getCurrentTime() const
	{
		return static_cast<float>(glfwGetTime());
	}
	const scope<Monitor> GLFWWindowContext::getPrimaryMonitor() const
	{
		TIME_FUNCTION;
		return std::make_unique<GLFWMonitor>(glfwGetPrimaryMonitor());
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
	void GLFWWindowContext::init0() const
	{
		TIME_FUNCTION;
		glfwInit();
	}
	ref<Window> GLFWWindowContext::createWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn& eventCallBack)
	{
		TIME_FUNCTION;
		return std::make_shared<GLFWWindow>(width, height, title, monitor, share, eventCallBack);
	}
	const uint32_t toGLFWType(const KEY& key)
	{
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
		case KEY::KEY_LAST:
			return GLFW_KEY_LAST;
			break;
		default:
			return GLFW_KEY_UNKNOWN;
			break;
		}
	}

	const uint32_t toGLFWType(const MOUSE& key)
	{
		switch (key) {
		case MOUSE::MOUSE_BUTTON_1:
			return GLFW_MOUSE_BUTTON_1;
			break;
		case MOUSE::MOUSE_BUTTON_2:
			return GLFW_MOUSE_BUTTON_2;
			break;
		case MOUSE::MOUSE_BUTTON_3:
			return GLFW_MOUSE_BUTTON_3;
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
		case MOUSE::MOUSE_BUTTON_LAST:
			return GLFW_MOUSE_BUTTON_LAST;
			break;
		case MOUSE::MOUSE_BUTTON_LEFT:
			return GLFW_MOUSE_BUTTON_LEFT;
			break;
		case MOUSE::MOUSE_BUTTON_RIGHT:
			return GLFW_MOUSE_BUTTON_RIGHT;
			break;
		case MOUSE::MOUSE_BUTTON_MIDDLE:
			return GLFW_MOUSE_BUTTON_MIDDLE;
			break;
		default:
			return GLFW_MOUSE_BUTTON_1;
			break;
		}
	}

	const KEY keyFromGLFWType(const int& key)
	{
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

	const MOUSE buttonFromGLFWType(const int& key)
	{
		switch (key)
		{
		case GLFW_MOUSE_BUTTON_1:
			return MOUSE::MOUSE_BUTTON_1;
			break;
		case GLFW_MOUSE_BUTTON_2:
			return MOUSE::MOUSE_BUTTON_2;
			break;
		case GLFW_MOUSE_BUTTON_3:
			return MOUSE::MOUSE_BUTTON_3;
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
			return MOUSE::MOUSE_BUTTON_1;
			break;
		}
	}
} // assec::graphics
