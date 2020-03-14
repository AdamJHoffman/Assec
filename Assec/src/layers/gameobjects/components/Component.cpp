#include "acpch.h"
#include "Component.h"

namespace assec::layersystem
{
	Component::Component(bool enabled) : m_Enabled(enabled) { TIME_FUNCTION; }
	Component::~Component() { TIME_FUNCTION; }
	void Component::onAttach()
	{
		TIME_FUNCTION;
	}
	void Component::onDetach()
	{
		TIME_FUNCTION;
	}
	bool Component::onWindowClose(events::WindowCloseEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowFocus(events::WindowFocusEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowFocusLost(events::WindowFocusLostEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowResize(events::WindowResizeEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowContentScale(events::WindowContentScaleEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowMove(events::WindowMoveEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowMinimize(events::WindowMinimizeEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowMaximize(events::WindowMaximizeEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowRestore(events::WindowRestoreEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onWindowRefresh(events::WindowRefreshEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onAppTick(events::AppTickEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onAppUpdate(events::AppUpdateEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onAppRender(events::AppRenderEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onPathDropped(events::PathDroppedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onKeyPressed(events::KeyPressedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onKeyReleased(events::KeyReleasedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onKeyRepeated(events::KeyRepeatedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onCharTyped(events::Event& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onMouseButtonPressed(events::MouseButtonPressedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onMouseButtonReleased(events::MouseButtonReleasedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onMouseMoved(events::MouseMovedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onMouseScrolled(events::MouseScrolledEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onCursorEntered(events::CursorEnteredEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
	bool Component::onCursorExited(events::CursorExitedEvent& event)
	{
		TIME_FUNCTION;
		return false;
	}
}
