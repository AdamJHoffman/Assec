#pragma once
#include "components/Component.h"

namespace assec::layersystem
{
	const class GameObject
	{
	public:
		GameObject(bool enabeld = true);
		virtual ~GameObject();
		inline const std::vector<ref<Component>> getGameObject() { return this->m_Components; }
		void onWindowClose(events::WindowCloseEvent& event);
		void onWindowFocus(events::WindowFocusEvent& event);
		void onWindowLostFocus(events::WindowFocusEvent& event);
		void onWindowResize(events::WindowResizeEvent& event);
		void onWindowContentScale(events::WindowContentScaleEvent& event);
		void onWindowMove(events::WindowMoveEvent& event);
		void onWindowMinimize(events::WindowMinimizeEvent& event);
		void onWindowMaximize(events::WindowMaximizeEvent& event);
		void onWindowRestore(events::WindowRestoreEvent& event);
		void onWindowRefresh(events::WindowRefreshEvent& event);
		void onAppTick(events::AppTickEvent& event);
		void onAppUpdate(events::AppUpdateEvent& event);
		void onAppRender(events::AppRenderEvent& event);
		void onPathDropped(events::PathDroppedEvent& event);
		void onKeyPressed(events::KeyPressedEvent& event);
		void onKeyReleased(events::KeyReleasedEvent& event);
		void onKeyRepeated(events::KeyRepeatedEvent& event);
		void onCharTyped(events::Event& event);
		void onMouseButtonPressed(events::MouseButtonPressedEvent& event);
		void onMouseButtonReleased(events::MouseButtonReleasedEvent& event);
		void onMouseMoved(events::MouseMovedEvent& event);
		void onMouseScrolled(events::MouseScrolledEvent& event);
		void onCursorEntered(events::CursorEnteredEvent& event);
		void onCursorExited(events::CursorExitedEvent& event);
		bool m_Enabled;
	private:
		std::vector<ref<Component>> m_Components;
	};
}
