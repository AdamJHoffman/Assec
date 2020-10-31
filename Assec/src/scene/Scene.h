#pragma once
#include "entt/entt.hpp"
#include <glm/glm.hpp>
#include "event/Event.h"

namespace assec::scene
{
	class Entity;
	class SceneSerializer;
	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity createEntity(const std::string & = "Unnamed Entity");
		void destroyEntity(const Entity&);
		void onEvent(const events::Event& event);
		inline const glm::mat4& getActiveCamera() const { return *this->m_ActiveCamera; }
		// TEMP
		inline entt::registry& reg() { return this->m_Registry; }
		inline const entt::registry& reg() const { return this->m_Registry; }
	private:
		entt::registry m_Registry;
		glm::mat4* m_ActiveCamera = nullptr;

		friend class Entity;
		friend class SceneSerializer;
	};
} // assec::scene
