#pragma once

#include <glm/glm.hpp>

#include "graphics/GraphicsContext.h"
#include "graphics/Monitor.h"
#include "graphics/Texture.h"

#include "event/Event.h"

namespace assec::graphics
{
	using EventCallBackFn = std::function<void(ref<events::Event>)>;

	struct Cursor
	{
		void* nativeCursor;
	};

	struct WindowIcon
	{
		WindowIcon(CONST_REF(Texture) texture) : width(texture.getWidth()), height(texture.getHeigth()),
			pixels((unsigned char*)texture.getData()) { TIME_FUNCTION; }
		int width,  height;
		unsigned char* pixels;
	};

	struct WindowData
	{
		WindowData(CONST_REF(EventCallBackFn) eventCallBack, CONST_REF(std::string) title, GraphicsContext* graphicsContext, const void* window) :  eventCallBack(eventCallBack), title(title), graphicsContext(graphicsContext), nativeWindow(window), swapInterval(1) { TIME_FUNCTION; }
		EventCallBackFn eventCallBack;
		std::string title = "Untitled Window";
		GraphicsContext* graphicsContext = nullptr;
		const void* nativeWindow = nullptr;
		uint32_t swapInterval = 0;
	};

	class Window
	{
	public:
		Window(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(std::string) title, CONST_REF(EventCallBackFn) eventCallBack, GraphicsContext* graphicsContext, const void* window) : m_WindowData(eventCallBack, title, graphicsContext, window) { TIME_FUNCTION; }
		virtual ~Window() { TIME_FUNCTION; }
		inline REF(WindowData) getWindowData() { TIME_FUNCTION; return this->m_WindowData; }
		inline CONST_REF(WindowData) getWindowData() const { TIME_FUNCTION; return this->m_WindowData; }		

		virtual void destroy() const = 0;
		virtual bool ShouldClose() const = 0;
		virtual void setShouldClose() const = 0;
		virtual void setTitle(CONST_REF(std::string)) = 0;
		virtual void setIcon(CONST_REF(WindowIcon)) const = 0;
		virtual glm::vec2 getPositon() const = 0;
		virtual void setPositon(CONST_REF(glm::vec2)) const = 0;
		virtual glm::vec2 getSize() const = 0;
		virtual void setSize(CONST_REF(glm::vec2)) const = 0;
		virtual void setSizeLimits(CONST_REF(glm::vec4)) const = 0;
		virtual void setAspectRatio(CONST_REF(glm::vec2)) const = 0;
		virtual glm::vec2 getFramebufferSize() const = 0;
		virtual glm::vec4 getFrameSize() const = 0;
		virtual glm::vec2 getContentScale() const = 0;
		virtual float getOpacity() const = 0;
		virtual void setOpacity(CONST_REF(float)) const = 0;
		virtual void iconify() const = 0;
		virtual void restore() const = 0;
		virtual void maximize() const = 0;

		virtual void show() const = 0;
		virtual void hide() const = 0;
		virtual void focus() const = 0;
		virtual void requestAttention() const = 0;
		virtual scope<Monitor> getMonitor() const = 0;
		virtual void setMonitor(CONST_REF(Monitor)) const = 0;
		virtual bool getAttrib(CONST_REF(WindowAttribute)) const = 0;
		virtual void setAttrib(CONST_REF(WindowAttribute), CONST_REF(bool)) const = 0;
		virtual void setUserPointer(void*) const = 0;
		virtual void* getUserPointer() const = 0;

		virtual void setPosCallback() const = 0;
		virtual void setSizeCallback() const = 0;
		virtual void setCloseCallback() const = 0;
		virtual void setRefreshCallback() const = 0;
		virtual void setFocusCallback() const = 0;
		virtual void setIconifyCallback() const = 0;
		virtual void setMaximizeCallback() const = 0;
		virtual void setFramebufferSizeCallback() const = 0;
		virtual void setContentScaleCallback() const = 0;
		virtual void setKeyCallback() const = 0;
		virtual void setCharCallback() const = 0;
		virtual void setCharModsCallback() const = 0;
		virtual void setMouseButtonCallback() const = 0;
		virtual void setCursorPosCallback() const = 0;
		virtual void setCursorEnterCallback() const = 0;
		virtual void setScrollCallback() const = 0;
		virtual void setDropCallback() const = 0;

		virtual CursorMode getCursorInputMode() const = 0;
		virtual bool isStickyKeysInputMode() const = 0;
		virtual bool isStickyMouseButtonsInputMode() const = 0;
		virtual bool istLockKeyModesInputMode() const = 0;
		virtual bool isRawMouseMotionInputMode() const = 0;

		virtual void setCursorInputMode(CONST_REF(CursorMode)) const = 0;
		virtual void setStickyKeysInputMode(CONST_REF(bool)) const = 0;
		virtual void setStickyMouseButtonsInputMode(CONST_REF(bool)) const = 0;
		virtual void settLockKeyModesInputMode(CONST_REF(bool)) const = 0;
		virtual void setRawMouseMotionInputMode(CONST_REF(bool)) const = 0;

		virtual bool getKey(CONST_REF(KEY)) const = 0;
		virtual bool getMouseButton(CONST_REF(MOUSE)) const = 0;
		virtual glm::vec2 getCursorPos() const = 0;
		virtual void setCursorPos(CONST_REF(glm::vec2)) const = 0;
		virtual void setCursor(CONST_REF(Cursor)) const = 0;

		virtual void setClipboardString(CONST_REF(std::string)) const = 0;
		virtual std::string getClipboardString() const = 0;
		virtual void makeContextCurrent() const = 0;
		virtual void swapBuffers() const = 0;
		virtual void swapInterval(CONST_REF(uint32_t)) const = 0;
	protected:
		virtual void* genWindow(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(std::string) title, const Monitor* monitor, const Window* share) const = 0;
		virtual void setupCallbacks() const = 0;
		WindowData m_WindowData;
	}; // namespace assec::graphics
}
