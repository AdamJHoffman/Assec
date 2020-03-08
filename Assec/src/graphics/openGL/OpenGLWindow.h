#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "graphics/Window.h"
#include "core/OpenGLConfig.h"
#include "graphics/openGL/OpenGLGraphicsContext.h"

namespace assec::graphics
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share, EventCallBackFn eventCallBack);
		virtual ~OpenGLWindow();
		virtual const void setUserPointer() const override;
		virtual const void terminate() const override;
		virtual const void validate() const override;
		virtual const void makeCurrent() const override;
		virtual const void swapBuffers() const override;
		virtual const void pollEvents() const override;
		virtual const void clear() const override;
		virtual const void setSize(unsigned int& width, unsigned int& height) const override;
		virtual const glm::vec2 getSize() const override;
		virtual const std::tuple<int, int, int, int> getFrameSize() const override;
		virtual const glm::vec2 getFramebufferSize() const override;
		virtual const glm::vec2 getWindowContentScale() const override;
		virtual const void setPosition(int& x, int& y) const override;
		virtual const glm::vec2 getPosition() const override;
		virtual const void setSizeLimits(unsigned int& minWidth, unsigned int& minHeight, unsigned int& maxWidth, unsigned int& maxHeight) const override;
		virtual const void setAspectRatio(unsigned int& width, unsigned int& height) const override;
		virtual const void setTitle(const char* title) const override;
		virtual const void minimize() const override;
		virtual const void restore() const override;
		virtual const void maximize() const override;
		virtual const void show() const override;
		virtual const void hide() const override;
		virtual const void focus() const override;
		virtual const void requestAttention() const override;
		virtual const void setOpacity(float opacity) const override;
		virtual const float getOpacity() const override;
		virtual const void setSwapInterval(unsigned int& interval) override;
		virtual const int getKeyState(int keycode) const override;
		virtual const int getMouseButtonState(int button) const override;
		virtual const void setClipboardString(const char* string) const override;
		virtual const char* getClipboardString() const override;
	protected:
		virtual void* createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const override;
		virtual const void setWindowResizeCallback() const override;
		virtual const void setFramebufferResizeCallback() const override;
		virtual const void setWindowContentScaleCallback() const override;
		virtual const void setCloseCallback() const override;
		virtual const void setMinimizeCallback() const override;
		virtual const void setMaximizeCallback() const override;
		virtual const void setFocusCallback() const override;
		virtual const void setRefreshCallback() const override;
		virtual const void setPosCallBack() const override;
		virtual const void setKeyCallback() const override;
		virtual const void setCharCallback() const override;
		virtual const void setMousePositionCallback() const override;
		virtual const void setCursorEnterCallback() const override;
		virtual const void setMouseButtonCallback() const override;
		virtual const void setMouseScrolledCallback() const override;
		virtual const void setPathDropCallback() const override;
	};
}
