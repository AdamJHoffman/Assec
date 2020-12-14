#pragma once

#pragma warning(push, 0)	// Disable warnings in external header
#include <entt/entt.hpp>
#pragma warning(pop)

#include "Scene.h"
#include "SceneSerializer.h"

#include "util/Orm.h"

namespace assec::scene
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const entt::entity& handle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity();

		template<typename T, typename... Args> T& addComponent(Args&&... args) const
		{
			AC_CORE_ASSERT(!this->hasComponent<T>(), "Entity already has component");
			auto& component = this->m_Scene->m_Registry.emplace<T>(this->m_EntityHandle, std::forward<Args>(args)...);
			this->m_Scene->onComponentAdded<T>(*this, component);
			return component;
		}
		template<typename T> void removeComponent() const
		{
			AC_CORE_ASSERT(this->hasComponent<T>(), "Entity does not have component");
			this->m_Scene->m_Registry.remove<T>(this->m_EntityHandle);
		}
		template<typename T> bool hasComponent() const
		{
			return this->m_Scene->m_Registry.valid(this->m_EntityHandle) ? this->m_Scene->m_Registry.has<T>(this->m_EntityHandle) : false;
		}
		template<typename T> T& getComponent()
		{
			AC_CORE_ASSERT(this->hasComponent<T>(), "Entity does not have component");
			return this->m_Scene->m_Registry.get<T>(this->m_EntityHandle);
		}
		template<typename T> const T& getComponent() const
		{
			AC_CORE_ASSERT(this->hasComponent<T>(), "Entity does not have component");
			return this->m_Scene->m_Registry.get<T>(this->m_EntityHandle);
		}
		const Scene& getScene() const
		{
			return *this->m_Scene;
		}
		Scene& getScene()
		{
			return *this->m_Scene;
		}
		uint32_t getNative() const
		{
			return static_cast<uint32_t>(this->m_EntityHandle);
		}
		operator bool() { return this->m_EntityHandle != entt::null && this->m_Scene != nullptr; }
		operator uint32_t () { return static_cast<uint32_t>(this->m_EntityHandle); }

		operator entt::entity() const { return m_EntityHandle; }

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

		friend class Scene;
		friend class SceneSerializer;
	};
}
