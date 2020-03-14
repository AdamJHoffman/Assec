#pragma once
#include "components/Component.h"

namespace assec::layersystem
{
	const class GameObject
	{
	public:
		GameObject(bool enabeld = true);
		~GameObject();
		inline const std::vector<ref<Component>>& getComponents() { TIME_FUNCTION; return this->m_Components; }
		inline void addComponent(const ref<Component> component) { TIME_FUNCTION; this->m_Components.push_back(component); }
		template<typename T>
		const bool hasComponent() const;
		template<typename T>
		const ref<T> getComponent() const;
		template<typename T>
		void removeComponent();
		void onAttach();
		void onDetach();
		bool onWindowClose(events::WindowCloseEvent& event);
		bool onWindowFocus(events::WindowFocusEvent& event);
		bool onWindowFocusLost(events::WindowFocusLostEvent& event);
		bool onWindowResize(events::WindowResizeEvent& event);
		bool onWindowContentScale(events::WindowContentScaleEvent& event);
		bool onWindowMove(events::WindowMoveEvent& event);
		bool onWindowMinimize(events::WindowMinimizeEvent& event);
		bool onWindowMaximize(events::WindowMaximizeEvent& event);
		bool onWindowRestore(events::WindowRestoreEvent& event);
		bool onWindowRefresh(events::WindowRefreshEvent& event);
		bool onAppTick(events::AppTickEvent& event);
		bool onAppUpdate(events::AppUpdateEvent& event);
		bool onAppRender(events::AppRenderEvent& event);
		bool onPathDropped(events::PathDroppedEvent& event);
		bool onKeyPressed(events::KeyPressedEvent& event);
		bool onKeyReleased(events::KeyReleasedEvent& event);
		bool onKeyRepeated(events::KeyRepeatedEvent& event);
		bool onCharTyped(events::Event& event);
		bool onMouseButtonPressed(events::MouseButtonPressedEvent& event);
		bool onMouseButtonReleased(events::MouseButtonReleasedEvent& event);
		bool onMouseMoved(events::MouseMovedEvent& event);
		bool onMouseScrolled(events::MouseScrolledEvent& event);
		bool onCursorEntered(events::CursorEnteredEvent& event);
		bool onCursorExited(events::CursorExitedEvent& event);
		bool m_Enabled;
	private:
		std::vector<ref<Component>> m_Components;
	};
}
