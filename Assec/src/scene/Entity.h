#pragma once
#include "Scene.h"
#include "entt/entt.hpp"
#include "Components.h"

namespace assec::scene
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity();

		template<typename T> bool hasComponent() const
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
		operator bool() const { return this->m_EntityHandle != entt::null; }
		operator uint32_t () { return (uint32_t)this->m_EntityHandle; }
		operator const uint32_t() const { (uint32_t)this->m_EntityHandle; }
		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}
