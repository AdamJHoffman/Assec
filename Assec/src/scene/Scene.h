#pragma once
#include "entt/entt.hpp"
#include <glm/glm.hpp>

namespace assec::scene
{
	class Entity;
	class Scene
	{
		friend class Entity;
	public:
		Scene();
		~Scene();
		const Entity createEntity();
		void setActiveCamera(glm::mat4& camera);
		inline const glm::mat4& getActiveCamera() const { return *this->m_ActiveCamera; }
		// TEMP
		inline entt::registry& reg() { return this->m_Registry; }
	private:
		entt::registry m_Registry;
		glm::mat4* m_ActiveCamera = nullptr;
	};
} // assec::scene
