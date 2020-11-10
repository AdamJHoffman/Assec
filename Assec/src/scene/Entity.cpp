#include "acpch.h"

#include "Entity.h"

namespace assec::scene
{
	Entity::Entity(const entt::entity& handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene) {}
	Entity::~Entity() {}
}
