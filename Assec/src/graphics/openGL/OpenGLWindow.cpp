#include "acpch.h"
#include "OpenGLWindow.h"

namespace assec::graphics
{
	OpenGLWindow::OpenGLWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack)
		: Window::Window(width, height, title, eventCallBack, new OpenGLGraphicsContext(), this->createWindow(width, height, title, monitor, share))
	{
		this->validate();
		this->makeCurrent();
		this->m_WindowData.m_GraphicsContext->init();
		this->setUserPointer();
		this->setWindowResizeCallback();
		this->setFramebufferResizeCallback();
		this->setWindowContentScaleCallback();
		this->setCloseCallback();
		this->setMinimizeCallback();
		this->setMaximizeCallback();
		this->setFocusCallback();
		this->setRefreshCallback();
		this->setPosCallBack();
		this->setSwapInterval(this->m_WindowData.m_SwapInterval);
	}
	OpenGLWindow::~OpenGLWindow()
	{
		this->terminate();
	}
	const void OpenGLWindow::setUserPointer() const
	{
		glfwSetWindowUserPointer((GLFWwindow*)this->m_WindowData.m_NativeWindow, (void*)this);
	}
	const void OpenGLWindow::terminate() const
	{
		glfwDestroyWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
		delete this->m_WindowData.m_GraphicsContext;
	}
	const void OpenGLWindow::validate() const
	{
		if (this->m_WindowData.m_NativeWindow == NULL)
		{
			this->~OpenGLWindow();
			ASSEC_CORE_CRITICAL("failed to initialize GLFW");
		}
		ASSEC_CORE_INFO("successfully initlialized GLFW: ");
		ASSEC_CORE_INFO("	Version: {0}", glfwGetVersionString());
	}
	const void OpenGLWindow::makeCurrent() const
	{
		glfwMakeContextCurrent((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::swapBuffers() const
	{
		glfwSwapBuffers((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::pollEvents() const
	{
		glfwPollEvents();
	}
	const void OpenGLWindow::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	const void OpenGLWindow::setSize(unsigned int& width, unsigned int& height) const
	{
		glfwSetWindowSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, width, height);
	}
	const glm::vec2 OpenGLWindow::getSize() const
	{
		int width, height;
		glfwGetWindowSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &width, &height);
		return glm::vec2(width, height);
	}
	const WindowSizeData OpenGLWindow::getFrameSize() const
	{
		int left, top, right, bottom;
		glfwGetWindowFrameSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &left, &top, &right, &bottom);
		return WindowSizeData((unsigned int&)left, (unsigned int&)top, (unsigned int&)right, (unsigned int&)bottom);
	}
	const glm::vec2 OpenGLWindow::getFramebufferSize() const
	{
		int width, height;
		glfwGetFramebufferSize((GLFWwindow*)this->m_WindowData.m_NativeWindow, &width, &height);
		return glm::vec2(width, height);
	}
	const glm::vec2 OpenGLWindow::getWindowContentScale() const
	{
		float xscale, yscale;
		glfwGetWindowContentScale((GLFWwindow*)this->m_WindowData.m_NativeWindow, &xscale, &yscale);
		return glm::vec2(xscale, yscale);
	}
	const void OpenGLWindow::setPosition(int& x, int& y) const
	{
		glfwSetWindowPos((GLFWwindow*)this->m_WindowData.m_NativeWindow, x, y);
	}
	const glm::vec2 OpenGLWindow::getPosition() const
	{
		int x, y;
		glfwGetWindowPos((GLFWwindow*)this->m_WindowData.m_NativeWindow, &x, &y);
		return glm::vec2(x, y);
	}
	const void OpenGLWindow::setSizeLimits(unsigned int& minWidth, unsigned int& minHeight, unsigned int& maxWidth, unsigned int& maxHeight) const
	{
		glfwSetWindowSizeLimits((GLFWwindow*)this->m_WindowData.m_NativeWindow, minWidth, minHeight, maxWidth, maxHeight);
	}
	const void OpenGLWindow::setAspectRatio(unsigned int& width, unsigned int& height) const
	{
		glfwSetWindowAspectRatio((GLFWwindow*)this->m_WindowData.m_NativeWindow, width, height);
	}
	const void OpenGLWindow::setTitle(const char* title) const
	{
		glfwSetWindowTitle((GLFWwindow*)this->m_WindowData.m_NativeWindow, title);
	}
	const void OpenGLWindow::minimize() const
	{
		glfwIconifyWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::restore() const
	{
		glfwRestoreWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::maximize() const
	{
		glfwMaximizeWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::show() const
	{
		glfwShowWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::hide() const
	{
		glfwHideWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::focus() const
	{
		glfwFocusWindow((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::requestAttention() const
	{
		glfwRequestWindowAttention((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::setOpacity(float opacity) const
	{
		glfwSetWindowOpacity((GLFWwindow*)this->m_WindowData.m_NativeWindow, opacity);
	}
	const float OpenGLWindow::getOpacity() const
	{
		return glfwGetWindowOpacity((GLFWwindow*)this->m_WindowData.m_NativeWindow);
	}
	const void OpenGLWindow::setSwapInterval(unsigned int& interval) const
	{
		glfwSwapInterval(interval);
	}
	void* OpenGLWindow::createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const
	{
		return glfwCreateWindow(width, height, title, (GLFWmonitor*)monitor, (GLFWwindow*)share);
	}
	const void OpenGLWindow::setWindowResizeCallback() const
	{
		glfwSetWindowSizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(events::WindowResizeEvent((void*)&window, (unsigned int&)width, (unsigned int&)height));
				window.getWindowData().m_Height = height;
				window.getWindowData().m_Width = width;
			});
	}
	const void OpenGLWindow::setFramebufferResizeCallback() const
	{
		glfwSetFramebufferSizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				glViewport(0, 0, width, height);
			});
	}
	const void OpenGLWindow::setWindowContentScaleCallback() const
	{
		glfwSetWindowContentScaleCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, float xscale, float yscale)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(events::WindowContentScaleEvent((void*)&window, xscale, yscale));
			});
	}
	const void OpenGLWindow::setCloseCallback() const
	{
		glfwSetWindowCloseCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(events::WindowCloseEvent((void*)&window));
				glfwSetWindowShouldClose(nativeWindow, true);
				window.getWindowData().m_Open = false;
			});
	}
	const void OpenGLWindow::setMinimizeCallback() const
	{
		glfwSetWindowIconifyCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int isIcon)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (isIcon)
				{
					window.getWindowData().m_EventCallBack(events::WindowMinimizeEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(events::WindowRestoreEvent((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setMaximizeCallback() const
	{
		glfwSetWindowMaximizeCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int maximized)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (maximized)
				{
					window.getWindowData().m_EventCallBack(events::WindowMaximizeEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(events::WindowRestoreEvent((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setFocusCallback() const
	{
		glfwSetWindowFocusCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int focused)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (focused)
				{
					window.getWindowData().m_EventCallBack(events::WindowFocusEvent((void*)&window));
				}
				else
				{
					window.getWindowData().m_EventCallBack(events::WindowFocusLostEvent((void*)&window));
				}
			});
	}
	const void OpenGLWindow::setRefreshCallback() const
	{
		glfwSetWindowRefreshCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(events::WindowRefreshEvent((void*)&window));
				window.swapBuffers();
			});
	}
	const void OpenGLWindow::setPosCallBack() const
	{
		glfwSetWindowPosCallback((GLFWwindow*)this->m_WindowData.m_NativeWindow, [](GLFWwindow* nativeWindow, int x, int y)
			{
				OpenGLWindow& window = *((OpenGLWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().m_EventCallBack(events::WindowMoveEvent((void*)&window, (int&)x, (int&)y));
			});
	}
}
