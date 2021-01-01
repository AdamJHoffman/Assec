#pragma once

#pragma warning(push, 0)	// Disable warnings in external header
#include <entt/entt.hpp>
#pragma warning(pop)
#include <glm/glm.hpp>

#include "event/Event.h"

namespace assec::scene
{
	class Entity;
	class SceneSerializer;
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;
		void onEvent(const events::Event& event);
		void onViewportResized(float width, float height);
		INLINE const glm::mat4& getActiveCamera() const { return this->m_ActiveCamera; }
		INLINE void setActiveCamera(CONST_REF(glm::mat4) camera) { this->m_ActiveCamera = camera; }
		INLINE std::string& getSaveFilePath() { return this->m_SaveFilePath; }
		Entity createEntity(const std::string & = "Unnamed Entity");
		Entity createEntity(CONST_REF(uint32_t) hint, const std::string & = "Unnamed Entity");
		// TEMP
		inline entt::registry& reg() { return this->m_Registry; }
	private:
		template<typename T>
		void onComponentAdded(const Entity&, T& component);

		entt::registry m_Registry = entt::registry();
		glm::mat4& m_ActiveCamera = glm::mat4(1.0f);
		std::string m_SaveFilePath;

		friend class Entity;
		friend class SceneSerializer;
	};
} // assec::scene
