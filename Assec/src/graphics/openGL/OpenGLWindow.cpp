#include "acpch.h"
#include "core/Core.h"
#include "OpenGLWindow.h"

namespace assec::graphics
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		AC_CORE_CRITICAL("GLFW Error ({0}): {1}", error, description);
	}

	OpenGLWindow::OpenGLWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack)
		: Window::Window(width, height, title, eventCallBack, new OpenGLGraphicsContext(), this->createWindow(width, height, title, monitor, share))
	{
		this->validate();
		this->makeCurrent();
		this->m_WindowData.m_GraphicsContext->init();
		this->setUserPointer();
		this->setSwapInterval(this->m_WindowData.m_SwapInterval);
		this->setWindowResizeCallback();
		this->setFramebufferResizeCallback();
		this->setWindowContentScaleCallback();
		this->setCloseCallback();
		this->setMinimizeCallback();
		this->setMaximizeCallback();
		this->setFocusCallback();
		this->setRefreshCallback();
		this->setPosCallBack();
		this->setKeyCallback();
		this->setCharCallback();
		this->setMousePositionCallback();
		this->setCursorEnterCallback();
		this->setMouseButtonCallback();
		this->setMouseScrolledCallback();
		this->setPathDropCallback();
	}
	OpenGLWindow::~OpenGLWindow()
	{
		this->terminate();
	}
	const void OpenGLWindow::setUserPointer() const
	{
		TIME_FUNCTION;
		glfwSetWindowUserPointer((GLFWwindow*)this->m_WindowData.m_NativeWindow, (void*)this);
	}
	const void OpenGLWindow::terminate() const
	{
		TIME_FUNCTION;
		delete this->m_WindowData.m_GraphicsContext;
		glfwDestroyWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::validate() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(!this->m_WindowData.m_NativeWindow == NULL, "Assertion failed: {0}", "failed to create GLFW window");
		AC_CORE_INFO("successfully created GLFW window: ");
		AC_CORE_INFO("	Version: {0}", glfwGetVersionString());
	}
	const void OpenGLWindow::makeCurrent() const
	{
		TIME_FUNCTION;
		glfwMakeContextCurrent((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::swapBuffers() const
	{
		TIME_FUNCTION;
		glfwSwapBuffers((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::pollEvents() const
	{
		TIME_FUNCTION;
		glfwPollEvents();
	}
	const void OpenGLWindow::clear() const
	{
		TIME_FUNCTION;
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	const void OpenGLWindow::setSize(unsigned int& width, unsigned int& height) const
	{
		TIME_FUNCTION;
		glfwSetWindowSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, width, height);
	}
	const glm::vec2 OpenGLWindow::getSize() const
	{
		TIME_FUNCTION;
		int width, height;
		glfwGetWindowSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &width, &height);
		return glm::vec2(width, height);
	}
	const std::tuple<int, int, int, int> OpenGLWindow::getFrameSize() const
	{
		TIME_FUNCTION;
		int left, top, right, bottom;
		glfwGetWindowFrameSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &left, &top, &right, &bottom);
		return { left, top, right, bottom };
	}
	const glm::vec2 OpenGLWindow::getFramebufferSize() const
	{
		TIME_FUNCTION;
		int width, height;
		glfwGetFramebufferSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &width, &height);
		return glm::vec2(width, height);
	}
	const glm::vec2 OpenGLWindow::getWindowContentScale() const
	{
		TIME_FUNCTION;
		float xscale, yscale;
		glfwGetWindowContentScale((GLFWwindow*)this->m_WindowData.m_NativeWindow, &xscale, &yscale);
		return glm::vec2(xscale, yscale);
	}
	const void OpenGLWindow::setPosition(int& x, int& y) const
	{
		TIME_FUNCTION;
		glfwSetWindowPos((GLFWwindow*)this->m_WindowData.m_NativeWindow, x, y);
	}
	const glm::vec2 OpenGLWindow::getPosition() const
	{
		TIME_FUNCTION;
		int x, y;
		glfwGetWindowPos((GLFWwindow*)this->m_WindowData.m_NativeWindow, &x, &y);
		return glm::vec2(x, y);
	}
	const void OpenGLWindow::setSizeLimits(unsigned int& minWidth, unsigned int& minHeight, unsigned int& maxWidth, unsigned int& maxHeight) const
	{
		TIME_FUNCTION;
		glfwSetWindowSizeLimits((GLFWwindow*)this->m_WindowData.m_NativeWindow, minWidth, minHeight, maxWidth, maxHeight);
	}
	const void OpenGLWindow::setAspectRatio(unsigned int& width, unsigned int& height) const
	{
		TIME_FUNCTION;
		glfwSetWindowAspectRatio((GLFWwindow*)this->m_WindowData.m_NativeWindow, width, height);
	}
	const void OpenGLWindow::setTitle(const char* title) const
	{
		TIME_FUNCTION;
		glfwSetWindowTitle((GLFWwindow*)this->m_WindowData.m_NativeWindow, title);
	}
	const void OpenGLWindow::minimize() const
	{
		TIME_FUNCTION;
		glfwIconifyWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::restore() const
	{
		TIME_FUNCTION;
		glfwRestoreWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::maximize() const
	{
		TIME_FUNCTION;
		glfwMaximizeWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::show() const
	{
		TIME_FUNCTION;
		glfwShowWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::hide() const
	{
		TIME_FUNCTION;
		glfwHideWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::focus() const
	{
		TIME_FUNCTION;
		glfwFocusWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::requestAttention() const
	{
		TIME_FUNCTION;
		glfwRequestWindowAttention((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::setOpacity(float opacity) const
	{
		TIME_FUNCTION;
		glfwSetWindowOpacity((GLFWwindow*)this->m_WindowData.m_NativeWindow, opacity);
	}
	const float OpenGLWindow::getOpacity() const
	{
		TIME_FUNCTION;
		return glfwGetWindowOpacity((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const int OpenGLWindow::getKeyState(int keycode) const
	{
		TIME_FUNCTION;
		return glfwGetKey((GLFWwindow*)this->m_WindowData.m_NativeWindow, keycode);
	}
	const int OpenGLWindow::getMouseButtonState(int button) const
	{
		TIME_FUNCTION;
		return glfwGetMouseButton((GLFWwindow*)this->m_WindowData.m_NativeWindow, button);
	}
	const void OpenGLWindow::setClipboardString(const char* string) const
	{
		TIME_FUNCTION;
		glfwSetClipboardString((GLFWwindow*)this->m_WindowData.m_NativeWindow, string);
	}
	const char* OpenGLWindow::getClipboardString() const
	{
		TIME_FUNCTION;
		return glfwGetClipboardString((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::setSwapInterval(unsigned int& interval)
	{
		TIME_FUNCTION;
		this->m_WindowData.m_SwapInterval = interval;
		glfwSwapInterval(interval);
	}
	void* OpenGLWindow::createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const
	{
		TIME_FUNCTION;
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AC_CORE_ASSERT(success, "Assertion failed: {0}", "Could not initialze GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		return glfwCreateWindow(width, height, title, (GLFWmonitor*)monitor, (GLFWwindow*)share);
	}
	const void OpenGLWindow::setWindowResizeCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowSizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::WindowResizeEvent>((void*)&window, (unsigned int&)width, (unsigned int&)height));
				window.getWindowData().m_Height = height;
				window.getWindowData().m_Width = width;
			});
	}
	const void OpenGLWindow::setFramebufferResizeCallback() const
	{
		TIME_FUNCTION;
		glfwSetFramebufferSizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				TIME_FUNCTION;
				glViewport(0, 0, width, height);
			});
	}
	const void OpenGLWindow::setWindowContentScaleCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowContentScaleCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, float xscale, float yscale)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::WindowContentScaleEvent>((void*)&window, xscale, yscale));
			});
	}
	const void OpenGLWindow::setCloseCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowCloseCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				glfwSetWindowShouldClose(nativeWindow, true);
				window.getWindowData().m_Open = false;
				window.getWindowData().m_EventCallBack(std::make_shared<events::WindowCloseEvent>((void*)&window));
			});
	}
	const void OpenGLWindow::setMinimizeCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowIconifyCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int isIcon)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (isIcon)
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::WindowMinimizeEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::WindowRestoreEvent>((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setMaximizeCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowMaximizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int maximized)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (maximized)
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::WindowMaximizeEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::WindowRestoreEvent>((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setFocusCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowFocusCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int focused)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (focused)
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::WindowFocusEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::WindowFocusLostEvent>((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setRefreshCallback() const
	{
		TIME_FUNCTION;
		glfwSetWindowRefreshCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::WindowRefreshEvent>((void*)&window));
				window.swapBuffers();
			});
	}
	const void OpenGLWindow::setPosCallBack() const
	{
		TIME_FUNCTION;
		glfwSetWindowPosCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int x, int y)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::WindowMoveEvent>((void*)&window, (int&)x, (int&)y));
			});
	}
	const void OpenGLWindow::setKeyCallback() const
	{
		TIME_FUNCTION;
		glfwSetKeyCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int keycode, int scancode, int action, int mods)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				switch (action)
				{
				case GLFW_PRESS:
					window.getWindowData().m_EventCallBack(std::make_shared<events::KeyPressedEvent>((void*)&window, keycode, scancode, mods));
					break;
				case GLFW_REPEAT:
					window.getWindowData().m_EventCallBack(std::make_shared<events::KeyRepeatedEvent>((void*)&window, keycode, scancode, mods));
					break;
				case GLFW_RELEASE:
					window.getWindowData().m_EventCallBack(std::make_shared<events::KeyReleasedEvent>((void*)&window, keycode, scancode));
					break;
				}
			});
	}
	const void OpenGLWindow::setCharCallback() const
	{
		TIME_FUNCTION;
		glfwSetCharCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, unsigned int unicode)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::CharTypedEvent>((void*)&window, unicode));
			});
	}
	const void OpenGLWindow::setMousePositionCallback() const
	{
		glfwSetCursorPosCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, double x, double y)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::MouseMovedEvent>((void*)&window, glm::vec2(x, y)));
			});
	}
	const void OpenGLWindow::setCursorEnterCallback() const
	{
		TIME_FUNCTION;
		glfwSetCursorEnterCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int entered)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (entered)
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::CursorEnteredEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(std::make_shared<events::CursorExitedEvent>((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setMouseButtonCallback() const
	{
		TIME_FUNCTION;
		glfwSetMouseButtonCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int button, int action, int mods)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				switch (action)
				{
				case GLFW_PRESS:
					window.getWindowData().m_EventCallBack(std::make_shared<events::MouseButtonPressedEvent>((void*)&window, button, mods));
					break;
				case GLFW_RELEASE:
					window.getWindowData().m_EventCallBack(std::make_shared<events::MouseButtonReleasedEvent>((void*)&window, button));
					break;
				}
			});
	}
	const void OpenGLWindow::setMouseScrolledCallback() const
	{
		TIME_FUNCTION;
		glfwSetScrollCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, double xOffset, double yOffset)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::MouseScrolledEvent>((void*)&window, glm::vec2(xOffset, yOffset)));
			});
	}
	const void OpenGLWindow::setPathDropCallback() const
	{
		TIME_FUNCTION;
		glfwSetDropCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int count, const char** paths)
			{
				TIME_FUNCTION;
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(std::make_shared<events::PathDroppedEvent>((void*)&window, count, paths));
			});
	}
}
