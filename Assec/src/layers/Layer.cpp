#include "acpch.h"
#include "Layer.h"

namespace assec::layersystem
{
	Layer::Layer(bool enabled) : m_GameObjects(std::vector<ref<GameObject>>()), m_Enabled(enabled) { TIME_FUNCTION; }
	Layer::~Layer() { TIME_FUNCTION; }
	void Layer::onEvent(const events::Event& event)
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
					dispatcher.dispatch<events::AppRenderEvent>([object](events::AppRenderEvent& event) {TIME_FUNCTION; return object->onAppRender(event); });
				}
			}
			std::reverse(this->m_GameObjects.begin(), this->m_GameObjects.end());
		}
		else {
			for (auto object : this->m_GameObjects)
			{
				if (object->m_Enabled)
				{
					dispatcher.dispatch<events::WindowCloseEvent>([object](events::WindowCloseEvent& event) {TIME_FUNCTION; return object->onWindowClose(event); });
					dispatcher.dispatch<events::WindowFocusEvent>([object](events::WindowFocusEvent& event) {TIME_FUNCTION; return object->onWindowFocus(event); });
					dispatcher.dispatch<events::WindowFocusLostEvent>([object](events::WindowFocusLostEvent& event) {TIME_FUNCTION; return object->onWindowFocusLost(event); });
					dispatcher.dispatch<events::WindowResizeEvent>([object](events::WindowResizeEvent& event) {TIME_FUNCTION; return object->onWindowResize(event); });
					dispatcher.dispatch<events::WindowContentScaleEvent>([object](events::WindowContentScaleEvent& event) {TIME_FUNCTION; return object->onWindowContentScale(event); });
					dispatcher.dispatch<events::WindowMoveEvent>([object](events::WindowMoveEvent& event) {TIME_FUNCTION; return object->onWindowMove(event); });
					dispatcher.dispatch<events::WindowMinimizeEvent>([object](events::WindowMinimizeEvent& event) {TIME_FUNCTION; return object->onWindowMinimize(event); });
					dispatcher.dispatch<events::WindowMaximizeEvent>([object](events::WindowMaximizeEvent& event) {TIME_FUNCTION; return object->onWindowMaximize(event); });
					dispatcher.dispatch<events::WindowRestoreEvent>([object](events::WindowRestoreEvent& event) {TIME_FUNCTION; return object->onWindowRestore(event); });
					dispatcher.dispatch<events::WindowRefreshEvent>([object](events::WindowRefreshEvent& event) {TIME_FUNCTION; return object->onWindowRefresh(event); });
					dispatcher.dispatch<events::AppTickEvent>([object](events::AppTickEvent& event) {TIME_FUNCTION; return object->onAppTick(event); });
					dispatcher.dispatch<events::AppUpdateEvent>([object](events::AppUpdateEvent& event) {TIME_FUNCTION; return object->onAppUpdate(event); });
					dispatcher.dispatch<events::PathDroppedEvent>([object](events::PathDroppedEvent& event) {TIME_FUNCTION; return object->onPathDropped(event); });
					dispatcher.dispatch<events::KeyPressedEvent>([object](events::KeyPressedEvent& event) {TIME_FUNCTION; return object->onKeyPressed(event); });
					dispatcher.dispatch<events::KeyReleasedEvent>([object](events::KeyReleasedEvent& event) {TIME_FUNCTION; return object->onKeyReleased(event); });
					dispatcher.dispatch<events::KeyRepeatedEvent>([object](events::KeyRepeatedEvent& event) {TIME_FUNCTION; return object->onKeyRepeated(event); });
					dispatcher.dispatch<events::CharTypedEvent>([object](events::CharTypedEvent& event) {TIME_FUNCTION; return object->onCharTyped(event); });
					dispatcher.dispatch<events::MouseButtonPressedEvent>([object](events::MouseButtonPressedEvent& event) {TIME_FUNCTION; return object->onMouseButtonPressed(event); });
					dispatcher.dispatch<events::MouseButtonReleasedEvent>([object](events::MouseButtonReleasedEvent& event) {TIME_FUNCTION; return object->onMouseButtonReleased(event); });
					dispatcher.dispatch<events::MouseMovedEvent>([object](events::MouseMovedEvent& event) {TIME_FUNCTION; return object->onMouseMoved(event); });
					dispatcher.dispatch<events::MouseScrolledEvent>([object](events::MouseScrolledEvent& event) {TIME_FUNCTION; return object->onMouseScrolled(event); });
					dispatcher.dispatch<events::CursorEnteredEvent>([object](events::CursorEnteredEvent& event) {TIME_FUNCTION; return object->onCursorEntered(event); });
					dispatcher.dispatch<events::CursorExitedEvent>([object](events::CursorExitedEvent& event) {TIME_FUNCTION; return object->onCursorExited(event); });
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
