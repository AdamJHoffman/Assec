#include "acpch.h"

#include <stb_image.h>

#include "platform/glfw/GLFWWindow.h"

#include "platform/glfw/GLFWWindowContext.h"
#include "platform/opengl/OpenGLGraphicsContext.h"

#include "platform/vulkan/VulkanGraphicsContext.h"

#include "event/WindowEvents.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"
#include "event/EngineEvents.h"

namespace assec::graphics
{

	static bool s_GLFWInitialized = false;

	GLFWWindow::GLFWWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn eventCallBack)
		: Window::Window(width, height, title, eventCallBack, new OpenGLGraphicsContext(), this->genWindow(width, height, title, monitor, share))
	{
		TIME_FUNCTION;
		this->validate();
		this->makeContextCurrent();
		this->m_WindowData.graphicsContext->init();
		this->setUserPointer((void*)this);
		this->swapInterval(this->m_WindowData.swapInterval);
		this->setupCallbacks();
	}
	GLFWWindow::~GLFWWindow()
	{
		TIME_FUNCTION;
	}

	void GLFWWindow::destroy() const 
	{
		glfwDestroyWindow(this->native());
	}
	bool GLFWWindow::ShouldClose() const 
	{
		return glfwWindowShouldClose(this->native());
	}
	void GLFWWindow::setShouldClose() const 
	{
		glfwSetWindowShouldClose(this->native(), true);
	}
	void GLFWWindow::setTitle(CONST_REF(std::string) title) 
	{
		this->m_WindowData.title = title;
		glfwSetWindowTitle(this->native(), title.c_str());
	}
	void GLFWWindow::setIcon(CONST_REF(WindowIcon) icon) const 
	{
		auto image = GLFWimage{ icon.width, icon.height, icon.pixels };
		glfwSetWindowIcon(this->native(), 1, &image);
	}
	glm::vec2 GLFWWindow::getPositon() const 
	{
		int x = 0, y = 0;
		glfwGetWindowPos(this->native(), &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y)};
	}
	void GLFWWindow::setPositon(CONST_REF(glm::vec2) position) const 
	{
		glfwSetWindowPos(this->native(), static_cast<int>(position.x), static_cast<int>(position.y));
	}
	glm::vec2 GLFWWindow::getSize() const 
	{
		int x = 0, y = 0;
		glfwGetWindowSize(this->native(), &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
	}
	void GLFWWindow::setSize(CONST_REF(glm::vec2) size) const
	{
		glfwSetWindowSize(this->native(), static_cast<int>(size.x), static_cast<int>(size.y));
	}

	void GLFWWindow::setSizeLimits(CONST_REF(glm::vec4) limits) const 
	{
		glfwSetWindowSizeLimits(this->native(), static_cast<int>(limits.x), static_cast<int>(limits.y),
			static_cast<int>(limits.z), static_cast<int>(limits.w));
	}
	void GLFWWindow::setAspectRatio(CONST_REF(glm::vec2) ratio) const 
	{
		glfwSetWindowAspectRatio(this->native(), static_cast<int>(ratio.x), static_cast<int>(ratio.y));
	}
	glm::vec2 GLFWWindow::getFramebufferSize() const 
	{
		int x = 0, y = 0;
		glfwGetFramebufferSize(this->native(), &x, &y);
		return glm::vec2{ static_cast<float>(x), static_cast<float>(y) };
	}
	glm::vec4 GLFWWindow::getFrameSize() const
	{
		int x = 0, y = 0, z = 0, w = 0;
		glfwGetWindowFrameSize(this->native(), &x, &y, &z, &w);
		return glm::vec4{ static_cast<float>(x), static_cast<float>(y), 
			static_cast<float>(z), static_cast<float>(w) };
	}
	glm::vec2 GLFWWindow::getContentScale() const 
	{
		glm::vec2 result = glm::vec2(0.0f);
		glfwGetWindowContentScale(this->native(), &result.x, &result.y);
		return result;
	}
	float GLFWWindow::getOpacity() const 
	{
		return glfwGetWindowOpacity(this->native());
	}
	void GLFWWindow::setOpacity(CONST_REF(float) opacity) const 
	{
		glfwSetWindowOpacity(this->native(), opacity);
	}
	void GLFWWindow::iconify() const 
	{
		glfwIconifyWindow(this->native());
	}
	void GLFWWindow::restore() const 
	{
		glfwRestoreWindow(this->native());
	}
	void GLFWWindow::maximize() const 
	{
		glfwMaximizeWindow(this->native());
	}
	void GLFWWindow::show() const 
	{
		glfwShowWindow(this->native());
	}
	void GLFWWindow::hide() const 
	{
		glfwHideWindow(this->native());
	}
	void GLFWWindow::focus() const 
	{
		glfwFocusWindow(this->native());
	}
	void GLFWWindow::requestAttention() const 
	{
		glfwRequestWindowAttention(this->native());
	}
	scope<Monitor> GLFWWindow::getMonitor() const 
	{
		return makeScope<GLFWMonitor>(glfwGetWindowMonitor(this->native()));
	}
	void GLFWWindow::setMonitor(CONST_REF(Monitor) monitor) const 
	{
		glfwSetWindowMonitor(this->native(), (GLFWmonitor*)monitor.getNativeMonitor(), 
			static_cast<int>(monitor.getPosition().x),
			static_cast<int>(monitor.getPosition().y), 
			static_cast<int>(monitor.getCurrentVideoMode().width),
			static_cast<int>(monitor.getCurrentVideoMode().height), 
			static_cast<int>(monitor.getCurrentVideoMode().refreshRate));
	}
	bool GLFWWindow::getAttrib(CONST_REF(WindowAttribute) attribute) const 
	{
		return glfwGetWindowAttrib(this->native(), toGLFWType(attribute));
	}
	void GLFWWindow::setAttrib(CONST_REF(WindowAttribute) attribute, CONST_REF(bool) value) const 
	{
		glfwSetWindowAttrib(this->native(), toGLFWType(attribute), static_cast<int>(value));
	}
	void GLFWWindow::setUserPointer(void* pointer) const 
	{
		glfwSetWindowUserPointer(this->native(), pointer);
	}
	void* GLFWWindow::getUserPointer() const 
	{
		return glfwGetWindowUserPointer(this->native());
	}

	void GLFWWindow::setPosCallback() const {}
	void GLFWWindow::setSizeCallback() const {}
	void GLFWWindow::setCloseCallback() const {}
	void GLFWWindow::setRefreshCallback() const {}
	void GLFWWindow::setFocusCallback() const {}
	void GLFWWindow::setIconifyCallback() const {}
	void GLFWWindow::setMaximizeCallback() const {}
	void GLFWWindow::setFramebufferSizeCallback() const {}
	void GLFWWindow::setContentScaleCallback() const {}
	void GLFWWindow::setKeyCallback() const {}
	void GLFWWindow::setCharCallback() const {}
	void GLFWWindow::setCharModsCallback() const {}
	void GLFWWindow::setMouseButtonCallback() const {}
	void GLFWWindow::setCursorPosCallback() const {}
	void GLFWWindow::setCursorEnterCallback() const {}
	void GLFWWindow::setScrollCallback() const {}
	void GLFWWindow::setDropCallback() const {}

	CursorMode GLFWWindow::getCursorInputMode() const 
	{
		return cursorModeFromGLFWType(glfwGetInputMode(this->native(), GLFW_CURSOR));
	}
	bool GLFWWindow::isStickyKeysInputMode() const 
	{
		return glfwGetInputMode(this->native(), GLFW_STICKY_KEYS);
	}
	bool GLFWWindow::isStickyMouseButtonsInputMode() const 
	{
		return glfwGetInputMode(this->native(), GLFW_STICKY_MOUSE_BUTTONS);
	}
	bool GLFWWindow::istLockKeyModesInputMode() const 
	{
		return glfwGetInputMode(this->native(), GLFW_LOCK_KEY_MODS);
	}
	bool GLFWWindow::isRawMouseMotionInputMode() const 
	{
		return glfwGetInputMode(this->native(), GLFW_RAW_MOUSE_MOTION);
	}

	void GLFWWindow::setCursorInputMode(CONST_REF(CursorMode) mode) const 
	{
		glfwSetInputMode(this->native(), GLFW_CURSOR, toGLFWType(mode));
	}
	void GLFWWindow::setStickyKeysInputMode(CONST_REF(bool) value) const 
	{
		glfwSetInputMode(this->native(), GLFW_STICKY_KEYS, static_cast<int>(value));
	}
	void GLFWWindow::setStickyMouseButtonsInputMode(CONST_REF(bool) value) const 
	{
		glfwSetInputMode(this->native(), GLFW_STICKY_MOUSE_BUTTONS, static_cast<int>(value));
	}
	void GLFWWindow::settLockKeyModesInputMode(CONST_REF(bool) value) const 
	{
		glfwSetInputMode(this->native(), GLFW_LOCK_KEY_MODS, static_cast<int>(value));
	}
	void GLFWWindow::setRawMouseMotionInputMode(CONST_REF(bool) value) const 
	{
		glfwSetInputMode(this->native(), GLFW_RAW_MOUSE_MOTION, static_cast<int>(value));
	}

	bool GLFWWindow::getKey(CONST_REF(KEY) key) const 
	{
		return glfwGetKey(this->native(), toGLFWType(key));
	}
	bool GLFWWindow::getMouseButton(CONST_REF(MOUSE) mouse) const 
	{
		return glfwGetMouseButton(this->native(), toGLFWType(mouse));
	}
	glm::vec2 GLFWWindow::getCursorPos() const 
	{
		double x = 0, y = 0;
		glfwGetCursorPos(this->native(), &x, &y);
		return glm::vec2(static_cast<float>(x), static_cast<float>(y));
	}
	void GLFWWindow::setCursorPos(CONST_REF(glm::vec2) position) const 
	{
		glfwSetCursorPos(this->native(), static_cast<float>(position.x), static_cast<float>(position.y));
	}
	void GLFWWindow::setCursor(CONST_REF(Cursor) cursor) const 
	{
		glfwSetCursor(this->native(), (GLFWcursor*)cursor.nativeCursor);
	}

	void GLFWWindow::setClipboardString(CONST_REF(std::string) string) const 
	{
		glfwSetClipboardString(this->native(), string.c_str());
	}
	std::string GLFWWindow::getClipboardString() const 
	{
		return std::string(glfwGetClipboardString(this->native()));
	}
	void GLFWWindow::makeContextCurrent() const 
	{
		glfwMakeContextCurrent(this->native());
	}
	void GLFWWindow::swapBuffers() const 
	{
		glfwSwapBuffers(this->native());
	}
	void GLFWWindow::swapInterval(CONST_REF(uint32_t) interval) const 
	{
		glfwSwapInterval(interval);
	}
	void GLFWWindow::validate() const
	{
		TIME_FUNCTION;
		AC_CORE_ASSERT(!this->m_WindowData.nativeWindow == NULL, "failed to create GLFW window");
		AC_CORE_INFO("successfully created GLFW window: ");
		AC_CORE_INFO("	Version: {0}", glfwGetVersionString());
	}
	
	void* GLFWWindow::genWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share) const
	{
		TIME_FUNCTION;
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AC_CORE_ASSERT(success, "Assertion failed: {0} Could not initialze GLFW!");
			s_GLFWInitialized = true;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		return glfwCreateWindow(width, height, title.c_str(), (GLFWmonitor*)(monitor == nullptr ? nullptr : monitor->getNativeMonitor()), (GLFWwindow*)(share == nullptr ? nullptr : share->getWindowData().nativeWindow));
	}
	void GLFWWindow::setupCallbacks() const
	{
		TIME_FUNCTION;
		glfwSetWindowSizeCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::WindowResizeEvent>((void*)&window, glm::vec2(static_cast<float>(width), static_cast<float>(height))));
			});
		glfwSetFramebufferSizeCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
			{
				TIME_FUNCTION;
				glViewport(0, 0, width, height);
			});
		glfwSetWindowContentScaleCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, float xscale, float yscale)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::WindowContentScaleEvent>((void*)&window, glm::vec2(static_cast<float>(xscale), static_cast<float>(yscale))));
			});
		glfwSetWindowCloseCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.setShouldClose();
				window.getWindowData().eventCallBack(std::make_shared<events::WindowCloseEvent>((void*)&window));
			});
		glfwSetWindowIconifyCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int isIcon)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (isIcon)
				{
					window.getWindowData().eventCallBack(std::make_shared<events::WindowMinimizeEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().eventCallBack(std::make_shared<events::WindowRestoreEvent>((void*)&window));
				}
			});
		glfwSetWindowMaximizeCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int maximized)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (maximized)
				{
					window.getWindowData().eventCallBack(std::make_shared<events::WindowMaximizeEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().eventCallBack(std::make_shared<events::WindowRestoreEvent>((void*)&window));
				}
			});
		glfwSetWindowFocusCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int focused)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (focused)
				{
					window.getWindowData().eventCallBack(std::make_shared<events::WindowFocusEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().eventCallBack(std::make_shared<events::WindowFocusLostEvent>((void*)&window));
				}
			});
		glfwSetWindowRefreshCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::WindowRefreshEvent>((void*)&window));
			});
		glfwSetWindowPosCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int x, int y)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::WindowMoveEvent>((void*)&window, glm::vec2(static_cast<float>(x), static_cast<float>(y))));
			});
		glfwSetKeyCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int keycode, int scancode, int action, int mods)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				switch (action)
				{
				case GLFW_PRESS:
					window.getWindowData().eventCallBack(std::make_shared<events::KeyPressedEvent>((void*)&window, keyFromGLFWType(keycode), scancode, mods));
					break;
				case GLFW_REPEAT:
					window.getWindowData().eventCallBack(std::make_shared<events::KeyRepeatedEvent>((void*)&window, keyFromGLFWType(keycode), scancode, mods));
					break;
				case GLFW_RELEASE:
					window.getWindowData().eventCallBack(std::make_shared<events::KeyReleasedEvent>((void*)&window, keyFromGLFWType(keycode), scancode));
					break;
				}
			});
		glfwSetCharCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, uint32_t unicode)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::CharTypedEvent>((void*)&window, unicode));
			});
		glfwSetCursorPosCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, double x, double y)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::MouseMovedEvent>((void*)&window, glm::vec2((float)x, (float)y)));
			});
		glfwSetCursorEnterCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int entered)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				if (entered)
				{
					window.getWindowData().eventCallBack(std::make_shared<events::CursorEnteredEvent>((void*)&window));
				}
				else
				{
					window.getWindowData().eventCallBack(std::make_shared<events::CursorExitedEvent>((void*)&window));
				}
			});
		glfwSetMouseButtonCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int button, int action, int mods)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				switch (action)
				{
				case GLFW_PRESS:
					window.getWindowData().eventCallBack(std::make_shared<events::MouseButtonPressedEvent>((void*)&window, buttonFromGLFWType(button), mods));
					break;
				case GLFW_RELEASE:
					window.getWindowData().eventCallBack(std::make_shared<events::MouseButtonReleasedEvent>((void*)&window, buttonFromGLFWType(button)));
					break;
				}
			});
		glfwSetScrollCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, double xOffset, double yOffset)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				window.getWindowData().eventCallBack(std::make_shared<events::MouseScrolledEvent>((void*)&window, glm::vec2(xOffset, yOffset)));
			});
		glfwSetDropCallback((GLFWwindow*)this->m_WindowData.nativeWindow, [](GLFWwindow* nativeWindow, int count, const char** paths)
			{
				TIME_FUNCTION;
				GLFWWindow& window = *((GLFWWindow*)glfwGetWindowUserPointer(nativeWindow));
				std::vector<std::string> strings(paths, paths + count);
				window.getWindowData().eventCallBack(std::make_shared<events::PathDroppedEvent>((void*)&window, strings));
			});
	}
} // namespace assec::graphics
