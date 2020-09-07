#pragma once
#include "entt/entt.hpp"
#include <glm/glm.hpp>
#include "event/Event.h"

namespace assec::scene
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity createEntity(const char* = "Unnamed Entity");
		void setActiveCamera(glm::mat4& camera);
		void onEvent(const events::Event& event);
		inline const glm::mat4& getActiveCamera() const { return *this->m_ActiveCamera; }
		// TEMP
		inline entt::registry& reg() { return this->m_Registry; }
	private:
		entt::registry m_Registry;
		glm::mat4* m_ActiveCamera = nullptr;

		friend class Entity;
	};
} // assec::scene
