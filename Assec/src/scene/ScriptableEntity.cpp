#include "acpch.h"

#include "ScriptableEntity.h"

namespace assec::scene
{
	ScriptableEntity::ScriptableEntity(const entt::entity& entity, Scene* scene) : m_Entity(entity, scene) {}
	void ScriptableEntity::onCreate() {}
	void ScriptableEntity::onDestroy() {}
	void ScriptableEntity::onEvent(const events::Event& event) {}
	std::map<std::string, ScriptableEntity*> ScriptableEntity::s_Scripts;
}