#include "acpch.h"
#include "GameObject.h"

namespace assec::layersystem
{
	GameObject::GameObject(bool enabled) : m_Components(std::vector<ref<Component>>()), m_Enabled(enabled) {}
	GameObject::~GameObject() {}
	void GameObject::onWindowClose(events::WindowCloseEvent& event) {}
	void GameObject::onWindowFocus(events::WindowFocusEvent& event) {}
	void GameObject::onWindowLostFocus(events::WindowFocusEvent& event) {}
	void GameObject::onWindowResize(events::WindowResizeEvent& event) {}
	void GameObject::onWindowContentScale(events::WindowContentScaleEvent& event) {}
	void GameObject::onWindowMove(events::WindowMoveEvent& event) {}
	void GameObject::onWindowMinimize(events::WindowMinimizeEvent& event) {}
	void GameObject::onWindowMaximize(events::WindowMaximizeEvent& event) {}
	void GameObject::onWindowRestore(events::WindowRestoreEvent& event) {}
	void GameObject::onWindowRefresh(events::WindowRefreshEvent& event) {}
	void GameObject::onAppTick(events::AppTickEvent& event) {}
	void GameObject::onAppUpdate(events::AppUpdateEvent& event) {}
	void GameObject::onAppRender(events::AppRenderEvent& event) {}
	void GameObject::onPathDropped(events::PathDroppedEvent& event) {}
	void GameObject::onKeyPressed(events::KeyPressedEvent& event) {}
	void GameObject::onKeyReleased(events::KeyReleasedEvent& event) {}
	void GameObject::onKeyRepeated(events::KeyRepeatedEvent& event) {}
	void GameObject::onCharTyped(events::Event& event) {}
	void GameObject::onMouseButtonPressed(events::MouseButtonPressedEvent& event) {}
	void GameObject::onMouseButtonReleased(events::MouseButtonReleasedEvent& event) {}
	void GameObject::onMouseMoved(events::MouseMovedEvent& event) {}
	void GameObject::onMouseScrolled(events::MouseScrolledEvent& event) {}
	void GameObject::onCursorEntered(events::CursorEnteredEvent& event) {}
	void GameObject::onCursorExited(events::CursorExitedEvent& event) {}
}
