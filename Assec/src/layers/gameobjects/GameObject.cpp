#include "acpch.h"
#include "GameObject.h"

namespace assec::layersystem
{
	GameObject::GameObject(bool enabled) : m_Components(std::vector<ref<Component>>()), m_Enabled(enabled) {}
	GameObject::~GameObject() {}
	template<typename T>
	const bool GameObject::hasComponent() const
	{
		TIME_FUNCTION;
		auto found = std::find_if(this->m_Components.begin(), this->m_Components.end(), [this](ref<T> component)
			{
				return component.getCommponentType() == T::getStaticType();
			});
		return found != this->m_Components.end();
	}
	template<typename T>
	void GameObject::removeComponent()
	{
		TIME_FUNCTION;
		auto found = std::find_if(this->m_Components.begin(), this->m_Components.end(), [this](ref<T> component)
			{
				return component.getCommponentType() == T::getStaticType();
			});
		if (found != this->m_Components.end())
		{
			this->m_Components.erase(found);
		}
	}
	template<typename T>
	const ref<T> GameObject::getComponent() const
	{
		TIME_FUNCTION;
		auto found = std::find_if(this->m_Components.begin(), this->m_Components.end(), [this](ref<T> component)
			{
				return component.getCommponentType() == T::getStaticType();
			});
		if (found != this->m_Components.end())
		{
			return found;
		}
		return nullptr;
	}
	void GameObject::onAttach()
	{
		TIME_FUNCTION;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled)
			{
				component->onAttach();
			}
		}
	}
	void GameObject::onDetach()
	{
		TIME_FUNCTION;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled)
			{
				component->onDetach();
			}
		}
	}
	bool GameObject::onWindowClose(events::WindowCloseEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowClose(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowFocus(events::WindowFocusEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowFocus(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowFocusLost(events::WindowFocusLostEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowFocusLost(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowResize(events::WindowResizeEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowResize(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowContentScale(events::WindowContentScaleEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowContentScale(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowMove(events::WindowMoveEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowMove(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowMinimize(events::WindowMinimizeEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowMinimize(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowMaximize(events::WindowMaximizeEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowMaximize(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowRestore(events::WindowRestoreEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowRestore(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onWindowRefresh(events::WindowRefreshEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onWindowRefresh(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onAppTick(events::AppTickEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onAppTick(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onAppUpdate(events::AppUpdateEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onAppUpdate(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onAppRender(events::AppRenderEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onAppRender(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onPathDropped(events::PathDroppedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onPathDropped(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onKeyPressed(events::KeyPressedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onKeyPressed(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onKeyReleased(events::KeyReleasedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onKeyReleased(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onKeyRepeated(events::KeyRepeatedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onKeyRepeated(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onCharTyped(events::Event& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onCharTyped(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onMouseButtonPressed(events::MouseButtonPressedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onMouseButtonPressed(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onMouseButtonReleased(events::MouseButtonReleasedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onMouseButtonReleased(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onMouseMoved(events::MouseMovedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onMouseMoved(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onMouseScrolled(events::MouseScrolledEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onMouseScrolled(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onCursorEntered(events::CursorEnteredEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onCursorEntered(event))
			{
				result = true;
			}
		}
		return result;
	}
	bool GameObject::onCursorExited(events::CursorExitedEvent& event)
	{
		TIME_FUNCTION;
		bool result = false;
		for (auto component : this->m_Components)
		{
			if (component->m_Enabled && component->onCursorExited(event))
			{
				result = true;
			}
		}
		return result;
	}
}
