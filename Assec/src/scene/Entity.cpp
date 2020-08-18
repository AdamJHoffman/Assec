#include "acpch.h"
#include "Entity.h"

namespace assec::scene
{
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene)
	{
		if (!this->hasComponent<TagComponent>())
			this->addComponent<TagComponent>("Unnamed Entity");
		if (!this->hasComponent<TransformComponent>())
			this->addComponent<TransformComponent>();
	}
	Entity::~Entity() {}
}
