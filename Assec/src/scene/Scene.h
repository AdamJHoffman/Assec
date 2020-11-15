#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "event/Event.h"

namespace assec::transactions
{
	class Transaction;
}

namespace assec::scene
{
	class Entity;
	class SceneSerializer;
	class Scene
	{
	public:
		Scene();
		~Scene();
		void onEvent(const events::Event& event);
		void onTransaction(const transactions::Transaction&);
		INLINE const glm::mat4& getActiveCamera() const { return this->m_ActiveCamera; }
		INLINE std::string& getSaveFilePath() { return this->m_SaveFilePath; }
		void setTransactionCallback(const std::function<void(ref<transactions::Transaction>)>&);
		// TEMP
		inline entt::registry& reg() { return this->m_Registry; }
	private:
		Entity createEntity(const std::string & = "Unnamed Entity");
		Entity createEntity(CONST_REF(uint32_t) hint, const std::string & = "Unnamed Entity");
		template<typename T>
		void onComponentAdded(const Entity&, T& component);

		entt::registry m_Registry = entt::registry();
		glm::mat4& m_ActiveCamera = glm::mat4(1.0f);
		std::function<void(ref<transactions::Transaction>)> m_TransactionCallback;
		std::string m_SaveFilePath;

		friend class Entity;
		friend class SceneSerializer;
	};
} // assec::scene
