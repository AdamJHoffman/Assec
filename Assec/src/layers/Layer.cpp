#include "acpch.h"
#include "Layer.h"

namespace assec::layersystem
{
	Layer::Layer(bool enabled) : m_GameObjects(std::vector<ref<GameObject>>()), m_Enabled(enabled) {}
	Layer::~Layer() {}
	void Layer::onEvent(events::Event& event)
	{
		TIME_FUNCTION;
		events::Dispatcher dispatcher = events::Dispatcher(event);
		if (event.getEventType() == events::EventType::AppRender)
		{
			std::reverse(this->m_GameObjects.begin(), this->m_GameObjects.end());
			for (auto object : this->m_GameObjects)
			{
				if (object->m_Enabled)
				{
					dispatcher.dispatch<events::AppRenderEvent>([object](events::AppRenderEvent& event) {return object->onAppRender(event); });
				}
			}
			std::reverse(this->m_GameObjects.begin(), this->m_GameObjects.end());
		}
		else {
			for (auto object : this->m_GameObjects)
			{
				if (object->m_Enabled)
				{
					dispatcher.dispatch<events::WindowCloseEvent>([object](events::WindowCloseEvent& event) {return object->onWindowClose(event); });
					dispatcher.dispatch<events::WindowFocusEvent>([object](events::WindowFocusEvent& event) {return object->onWindowFocus(event); });
					dispatcher.dispatch<events::WindowFocusLostEvent>([object](events::WindowFocusLostEvent& event) {return object->onWindowFocusLost(event); });
					dispatcher.dispatch<events::WindowResizeEvent>([object](events::WindowResizeEvent& event) {return object->onWindowResize(event); });
					dispatcher.dispatch<events::WindowContentScaleEvent>([object](events::WindowContentScaleEvent& event) {return object->onWindowContentScale(event); });
					dispatcher.dispatch<events::WindowMoveEvent>([object](events::WindowMoveEvent& event) {return object->onWindowMove(event); });
					dispatcher.dispatch<events::WindowMinimizeEvent>([object](events::WindowMinimizeEvent& event) {return object->onWindowMinimize(event); });
					dispatcher.dispatch<events::WindowMaximizeEvent>([object](events::WindowMaximizeEvent& event) {return object->onWindowMaximize(event); });
					dispatcher.dispatch<events::WindowRestoreEvent>([object](events::WindowRestoreEvent& event) {return object->onWindowRestore(event); });
					dispatcher.dispatch<events::WindowRefreshEvent>([object](events::WindowRefreshEvent& event) {return object->onWindowRefresh(event); });
					dispatcher.dispatch<events::AppTickEvent>([object](events::AppTickEvent& event) {return object->onAppTick(event); });
					dispatcher.dispatch<events::AppUpdateEvent>([object](events::AppUpdateEvent& event) {return object->onAppUpdate(event); });
					dispatcher.dispatch<events::PathDroppedEvent>([object](events::PathDroppedEvent& event) {return object->onPathDropped(event); });
					dispatcher.dispatch<events::KeyPressedEvent>([object](events::KeyPressedEvent& event) {return object->onKeyPressed(event); });
					dispatcher.dispatch<events::KeyReleasedEvent>([object](events::KeyReleasedEvent& event) {return object->onKeyReleased(event); });
					dispatcher.dispatch<events::KeyRepeatedEvent>([object](events::KeyRepeatedEvent& event) {return object->onKeyRepeated(event); });
					dispatcher.dispatch<events::CharTypedEvent>([object](events::CharTypedEvent& event) {return object->onCharTyped(event); });
					dispatcher.dispatch<events::MouseButtonPressedEvent>([object](events::MouseButtonPressedEvent& event) {return object->onMouseButtonPressed(event); });
					dispatcher.dispatch<events::MouseButtonReleasedEvent>([object](events::MouseButtonReleasedEvent& event) {return object->onMouseButtonReleased(event); });
					dispatcher.dispatch<events::MouseMovedEvent>([object](events::MouseMovedEvent& event) {return object->onMouseMoved(event); });
					dispatcher.dispatch<events::MouseScrolledEvent>([object](events::MouseScrolledEvent& event) {return object->onMouseScrolled(event); });
					dispatcher.dispatch<events::CursorEnteredEvent>([object](events::CursorEnteredEvent& event) {return object->onCursorEntered(event); });
					dispatcher.dispatch<events::CursorExitedEvent>([object](events::CursorExitedEvent& event) {return object->onCursorExited(event); });
				}
			}
		}
	}
	void Layer::onAttach()
	{
		TIME_FUNCTION;
		for (auto obj : this->m_GameObjects)
		{
			if (obj->m_Enabled)
			{
				obj->onAttach();
			}
		}
	}
	void Layer::onDetach()
	{
		TIME_FUNCTION;
		for (auto obj : this->m_GameObjects)
		{
			if (obj->m_Enabled)
			{
				obj->onDetach();
			}
		}
	}
}
