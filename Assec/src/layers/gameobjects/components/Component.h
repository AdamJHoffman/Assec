#pragma once

#define COMPONENT_CLASS_TYPE(type)	static ComponentType getStaticType() { TIME_FUNCTION; return  type;}\
									virtual const ComponentType getComponentType() const override { TIME_FUNCTION; return getStaticType(); }\

namespace assec::layersystem
{
	enum ComponentType
	{
		None = 0
	};
	class Component
	{
	public:
		Component(bool enabled = true);
		virtual ~Component();
		virtual const ComponentType getComponentType() const = 0;
		virtual void onAttach();
		virtual void onDetach();
		virtual bool onWindowClose(events::WindowCloseEvent& event);
		virtual bool onWindowFocus(events::WindowFocusEvent& event);
		virtual bool onWindowFocusLost(events::WindowFocusLostEvent& event);
		virtual bool onWindowResize(events::WindowResizeEvent& event);
		virtual bool onWindowContentScale(events::WindowContentScaleEvent& event);
		virtual bool onWindowMove(events::WindowMoveEvent& event);
		virtual bool onWindowMinimize(events::WindowMinimizeEvent& event);
		virtual bool onWindowMaximize(events::WindowMaximizeEvent& event);
		virtual bool onWindowRestore(events::WindowRestoreEvent& event);
		virtual bool onWindowRefresh(events::WindowRefreshEvent& event);
		virtual bool onAppTick(events::AppTickEvent& event);
		virtual bool onAppUpdate(events::AppUpdateEvent& event);
		virtual bool onAppRender(events::AppRenderEvent& event);
		virtual bool onPathDropped(events::PathDroppedEvent& event);
		virtual bool onKeyPressed(events::KeyPressedEvent& event);
		virtual bool onKeyReleased(events::KeyReleasedEvent& event);
		virtual bool onKeyRepeated(events::KeyRepeatedEvent& event);
		virtual bool onCharTyped(events::Event& event);
		virtual bool onMouseButtonPressed(events::MouseButtonPressedEvent& event);
		virtual bool onMouseButtonReleased(events::MouseButtonReleasedEvent& event);
		virtual bool onMouseMoved(events::MouseMovedEvent& event);
		virtual bool onMouseScrolled(events::MouseScrolledEvent& event);
		virtual bool onCursorEntered(events::CursorEnteredEvent& event);
		virtual bool onCursorExited(events::CursorExitedEvent& event);
		bool m_Enabled;
	};
}
