#pragma once

#include "graphics/Window.h"

#include "GLFWWindowContext.h"

#include "graphics/Monitor.h"

namespace assec::graphics
{

	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share, const EventCallBackFn eventCallBack);
		virtual ~GLFWWindow();

		virtual void destroy() const override;
		virtual bool ShouldClose() const override;
		virtual void setShouldClose() const override;
		virtual void setTitle(CONST_REF(std::string)) override;
		virtual void setIcon(CONST_REF(WindowIcon)) const override;
		virtual glm::vec2 getPositon() const override;
		virtual void setPositon(CONST_REF(glm::vec2)) const override;
		virtual glm::vec2 getSize() const override;
		virtual void setSize(CONST_REF(glm::vec2)) const override;
		virtual void setSizeLimits(CONST_REF(glm::vec4)) const override;
		virtual void setAspectRatio(CONST_REF(glm::vec2)) const override;
		virtual glm::vec2 getFramebufferSize() const override;
		virtual glm::vec4 getFrameSize() const override;
		virtual glm::vec2 getContentScale() const override;
		virtual float getOpacity() const override;
		virtual void setOpacity(CONST_REF(float)) const override;
		virtual void iconify() const override;
		virtual void restore() const override;
		virtual void maximize() const override;
		virtual void show() const override;
		virtual void hide() const override;
		virtual void focus() const override;
		virtual void requestAttention() const override;
		virtual scope<Monitor> getMonitor() const override;
		virtual void setMonitor(CONST_REF(Monitor)) const override;
		virtual bool getAttrib(CONST_REF(WindowAttribute)) const override;
		virtual void setAttrib(CONST_REF(WindowAttribute), CONST_REF(bool)) const override;
		virtual void setUserPointer(void*) const override;
		virtual void* getUserPointer() const override;

		virtual void setPosCallback() const override;
		virtual void setSizeCallback() const override;
		virtual void setCloseCallback() const override;
		virtual void setRefreshCallback() const override;
		virtual void setFocusCallback() const override;
		virtual void setIconifyCallback() const override;
		virtual void setMaximizeCallback() const override;
		virtual void setFramebufferSizeCallback() const override;
		virtual void setContentScaleCallback() const override;
		virtual void setKeyCallback() const override;
		virtual void setCharCallback() const override;
		virtual void setCharModsCallback() const override;
		virtual void setMouseButtonCallback() const override;
		virtual void setCursorPosCallback() const override;
		virtual void setCursorEnterCallback() const override;
		virtual void setScrollCallback() const override;
		virtual void setDropCallback() const override;

		virtual CursorMode getCursorInputMode() const override;
		virtual bool isStickyKeysInputMode() const override;
		virtual bool isStickyMouseButtonsInputMode() const override;
		virtual bool istLockKeyModesInputMode() const override;
		virtual bool isRawMouseMotionInputMode() const override;

		virtual void setCursorInputMode(CONST_REF(CursorMode)) const override;
		virtual void setStickyKeysInputMode(CONST_REF(bool)) const override;
		virtual void setStickyMouseButtonsInputMode(CONST_REF(bool)) const override;
		virtual void settLockKeyModesInputMode(CONST_REF(bool)) const override;
		virtual void setRawMouseMotionInputMode(CONST_REF(bool)) const override;

		virtual bool getKey(CONST_REF(KEY)) const override;
		virtual bool getMouseButton(CONST_REF(MOUSE)) const override;
		virtual glm::vec2 getCursorPos() const override;
		virtual void setCursorPos(CONST_REF(glm::vec2)) const override;
		virtual void setCursor(CONST_REF(Cursor)) const override;

		virtual void setClipboardString(CONST_REF(std::string)) const override;
		virtual std::string getClipboardString() const override;
		virtual void makeContextCurrent() const override;
		virtual void swapBuffers() const override;
		virtual void swapInterval(CONST_REF(uint32_t)) const override;
	protected:
		INLINE GLFWwindow* native() const { TIME_FUNCTION; return (GLFWwindow*)this->m_WindowData.nativeWindow; }
		virtual void validate() const;
		virtual void* genWindow(const uint32_t& width, const uint32_t& height, const std::string& title, const Monitor* monitor, const Window* share) const override;
		virtual void setupCallbacks() const override;
	};
} // assec::graphics
