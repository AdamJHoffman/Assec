#include "acpch.h"

#include "GLFWWindow.h"

#include "GLFWWindowContext.h"

#include "event/WindowEvents.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"
#include "event/EngineEvents.h"

namespace assec::graphics
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		TIME_FUNCTION;
		AC_CORE_CRITICAL("GLFW Error ({0}): {1}", error, description);
	}

	GLFWWindow::GLFWWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn eventCallBack)
		: Window::Window(width, height, title, eventCallBack, new OpenGLGraphicsContext(), this->createWindow(width, height, title, monitor, share))
	{
		TIME_FUNCTION;
		this->validate();
		this->makeCurrent();
		this->m_WindowData.m_GraphicsContext->init();
		this->setUserPointer();
		this->setSwapInterval(this->m_WindowData.m_SwapInterval);
		this->setupCallbacks();
	}
	GLFWWindow::~GLFWWindow()
	{
		TIME_FUNCTION;
	}
	void GLFWWindow::setUserPointer() const
	{
		TIME_FUNCTION;
		glfwSetWindowUserPointer((GLFWwindow*)this->m_WindowData.m_NativeWindow, (void*)this);
	}
	void GLFWWindow::cleanup() const
	{
		TIME_FUNCTION;
		delete this->m_WindowData.m_GraphicsContext;
		glfwDestroyWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::validate() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(!this->m_WindowData.m_NativeWindow == NULL, "Assertion failed: {0}", "failed to create GLFW window");
		AC_CORE_INFO("successfully created GLFW window: ");
		AC_CORE_INFO("	Version: {0}", glfwGetVersionString());
	}
	void GLFWWindow::makeCurrent() const
	{
		TIME_FUNCTION;
		glfwMakeContextCurrent((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::swapBuffers() const
	{
		TIME_FUNCTION;
		glfwSwapBuffers((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::pollEvents() const
	{
		TIME_FUNCTION;
		glfwPollEvents();
	}
	void GLFWWindow::clear() const
	{
		TIME_FUNCTION;
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	void GLFWWindow::setSize(const uint32_t& width, const uint32_t& height) const
	{
		TIME_FUNCTION;
		glfwSetWindowSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, width, height);
	}
	const glm::vec2 GLFWWindow::getSize() const
	{
		TIME_FUNCTION;
		int width, height;
		glfwGetWindowSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &width, &height);
		return glm::vec2(width, height);
	}
	const std::tuple<int, int, int, int> GLFWWindow::getFrameSize() const
	{
		TIME_FUNCTION;
		int left, top, right, bottom;
		glfwGetWindowFrameSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &left, &top, &right, &bottom);
		return { left, top, right, bottom };
	}
	const glm::vec2 GLFWWindow::getFramebufferSize() const
	{
		TIME_FUNCTION;
		int width, height;
		glfwGetFramebufferSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &width, &height);
		return glm::vec2(width, height);
	}
	const glm::vec2 GLFWWindow::getWindowContentScale() const
	{
		TIME_FUNCTION;
		float xscale, yscale;
		glfwGetWindowContentScale((GLFWwindow*)this->m_WindowData.m_NativeWindow, &xscale, &yscale);
		return glm::vec2(xscale, yscale);
	}
	void GLFWWindow::setPosition(const int& x, const int& y) const
	{
		TIME_FUNCTION;
		glfwSetWindowPos((GLFWwindow*)this->m_WindowData.m_NativeWindow, x, y);
	}
	const glm::vec2 GLFWWindow::getPosition() const
	{
		TIME_FUNCTION;
		int x, y;
		glfwGetWindowPos((GLFWwindow*)this->m_WindowData.m_NativeWindow, &x, &y);
		return glm::vec2(x, y);
	}
	void GLFWWindow::setSizeLimits(const uint32_t& minWidth, const uint32_t& minHeight, const uint32_t& maxWidth, const uint32_t& maxHeight) const
	{
		TIME_FUNCTION;
		glfwSetWindowSizeLimits((GLFWwindow*)this->m_WindowData.m_NativeWindow, minWidth, minHeight, maxWidth, maxHeight);
	}
	void GLFWWindow::setAspectRatio(const uint32_t& width, const uint32_t& height) const
	{
		TIME_FUNCTION;
		glfwSetWindowAspectRatio((GLFWwindow*)this->m_WindowData.m_NativeWindow, width, height);
	}
	void GLFWWindow::setTitle(const char* title) const
	{
		TIME_FUNCTION;
		glfwSetWindowTitle((GLFWwindow*)this->m_WindowData.m_NativeWindow, title);
	}
	void GLFWWindow::minimize() const
	{
		TIME_FUNCTION;
		glfwIconifyWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::restore() const
	{
		TIME_FUNCTION;
		glfwRestoreWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::maximize() const
	{
		TIME_FUNCTION;
		glfwMaximizeWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::show() const
	{
		TIME_FUNCTION;
		glfwShowWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::hide() const
	{
		TIME_FUNCTION;
		glfwHideWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::focus() const
	{
		TIME_FUNCTION;
		glfwFocusWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::requestAttention() const
	{
		TIME_FUNCTION;
		glfwRequestWindowAttention((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::setOpacity(const float& opacity) const
	{
		TIME_FUNCTION;
		glfwSetWindowOpacity((GLFWwindow*)this->m_WindowData.m_NativeWindow, opacity);
	}
	const float GLFWWindow::getOpacity() const
	{
		TIME_FUNCTION;
		return glfwGetWindowOpacity((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const int GLFWWindow::getKeyState(const int& keycode) const
	{
		TIME_FUNCTION;
		return glfwGetKey((GLFWwindow*)this->m_WindowData.m_NativeWindow, keycode);
	}
	const int GLFWWindow::getMouseButtonState(const int& button) const
	{
		TIME_FUNCTION;
		return glfwGetMouseButton((GLFWwindow*)this->m_WindowData.m_NativeWindow, button);
	}
	void GLFWWindow::setClipboardString(const char* string) const
	{
		TIME_FUNCTION;
		glfwSetClipboardString((GLFWwindow*)this->m_WindowData.m_NativeWindow, string);
	}
	const char* GLFWWindow::getClipboardString() const
	{
		TIME_FUNCTION;
		return glfwGetClipboardString((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	void GLFWWindow::setSwapInterval(const uint32_t& interval)
	{
		TIME_FUNCTION;
		this->m_WindowData.m_SwapInterval = interval;
		glfwSwapInterval(interval);
	}
	void* GLFWWindow::createWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share) const
	{
		TIME_FUNCTION;
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AC_CORE_ASSERT(success, "Assertion failed: {0}", "Could not initialze GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		return glfwCreateWindow(width, height, title.c_str(), (GLFWmonitor*)(monitor == nullptr ? nullptr : monitor->m_NativeMonitor), (GLFWwindow*)(share == nullptr ? nullptr : share->getWindowData().m_NativeWindow));
	}
	void GLFWWindow::setupCallbacks() const
	{
		TIME_FUNCTION;
		glfwSetWindowSizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::WindowResizeEvent((void*)&window, (uint32_t&)width, (uint32_t&)height));
				window.getWindowData().m_Height = height;
				window.getWindowData().m_Width = width;
			});
		glfwSetFramebufferSizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				TIME_FUNCTION;
				glViewport(0, 0, width, height);
			});
		glfwSetWindowContentScaleCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, float xscale, float yscale)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::WindowContentScaleEvent((void*)&window, xscale, yscale));
			});
		glfwSetWindowCloseCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				glfwSetWindowShouldClose(nativeWindow, true);
				window.getWindowData().m_Open = false;
				window.getWindowData().m_EventCallBack(new events::WindowCloseEvent((void*)&window));
			});
		glfwSetWindowIconifyCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int isIcon)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (isIcon)
				{
					window.getWindowData().m_EventCallBack(new events::WindowMinimizeEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(new events::WindowRestoreEvent((void*)&window));
				}
			});
		glfwSetWindowMaximizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int maximized)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (maximized)
				{
					window.getWindowData().m_EventCallBack(new events::WindowMaximizeEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(new events::WindowRestoreEvent((void*)&window));
				}
			});
		glfwSetWindowFocusCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int focused)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (focused)
				{
					window.getWindowData().m_EventCallBack(new events::WindowFocusEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(new events::WindowFocusLostEvent((void*)&window));
				}
			});
		glfwSetWindowRefreshCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::WindowRefreshEvent((void*)&window));
				window.swapBuffers();
			});
		glfwSetWindowPosCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int x, int y)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::WindowMoveEvent((void*)&window, (int&)x, (int&)y));
			});
		glfwSetKeyCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int keycode, int scancode, int action, int mods)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				switch (action)
				{
				case GLFW_PRESS:
					window.getWindowData().m_EventCallBack(new events::KeyPressedEvent((void*)&window, keyFromGLFWType(keycode), scancode, mods));
					break;
				case GLFW_REPEAT:
					window.getWindowData().m_EventCallBack(new events::KeyRepeatedEvent((void*)&window, keyFromGLFWType(keycode), scancode, mods));
					break;
				case GLFW_RELEASE:
					window.getWindowData().m_EventCallBack(new events::KeyReleasedEvent((void*)&window, keyFromGLFWType(keycode), scancode));
					break;
				}
			});
		glfwSetCharCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, uint32_t unicode)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::CharTypedEvent((void*)&window, unicode));
			});
		glfwSetCursorPosCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, double x, double y)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::MouseMovedEvent((void*)&window, glm::vec2((float)x, (float)y)));
			});
		glfwSetCursorEnterCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int entered)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (entered)
				{
					window.getWindowData().m_EventCallBack(new events::CursorEnteredEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(new events::CursorExitedEvent((void*)&window));
				}
			});
		glfwSetMouseButtonCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int button, int action, int mods)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				switch (action)
				{
				case GLFW_PRESS:
					window.getWindowData().m_EventCallBack(new events::MouseButtonPressedEvent((void*)&window, buttonFromGLFWType(button), mods));
					break;
				case GLFW_RELEASE:
					window.getWindowData().m_EventCallBack(new events::MouseButtonReleasedEvent((void*)&window, buttonFromGLFWType(button)));
					break;
				}
			});
		glfwSetScrollCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, double xOffset, double yOffset)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::MouseScrolledEvent((void*)&window, glm::vec2(xOffset, yOffset)));
			});
		glfwSetDropCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int count, const char** paths)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(new events::PathDroppedEvent((void*)&window, count, paths));
			});
	}
} // assec::graphics
