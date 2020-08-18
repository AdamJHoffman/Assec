#pragma once
#include "Scene.h"
#include "entt/entt.hpp"
#include "Components.h"

namespace assec::scene
{
	class Entity
	{
	public:
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity();

		template<typename T> bool hasComponent()
		{
			return this->m_Scene->m_Registry.has<T>(this->m_EntityHandle);
		}
		template<typename T, typename... Args> T& addComponent(Args&&... args)
		{
			AC_CORE_ASSERT_(!this->hasComponent<T>(), "Entity already has component");
			return this->m_Scene->m_Registry.emplace<T>(this->m_EntityHandle, std::forward<Args>(args)...);
		}
		template<typename T> T& getComponent()
		{
			AC_CORE_ASSERT_(this->hasComponent<T>(), "Entity already has component");
			return this->m_Scene->m_Registry.get<T>(this->m_EntityHandle);
		}
		template<typename T> const T& getComponent() const
		{
			AC_CORE_ASSERT_(this->hasComponent<T>(), "Entity already has component");
			return this->m_Scene->m_Registry.get<T>(this->m_EntityHandle);
		}
		template<typename T> void removeComponent()
		{
			AC_CORE_ASSERT_(this->hasComponent<T>(), "Entity already has component");
			this->m_Scene->m_Registry.remove<T>(this->m_EntityHandle);
		}
	private:
		entt::entity m_EntityHandle;
		Scene* m_Scene;
	};
}
