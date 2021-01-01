#include "acpch.h"

#include "Scene.h"
#include "Components.h"

#include "core/Application.h"

#include "graphics/WindowManager.h"

#include "event/EngineEvents.h"

namespace assec::scene
{
	Entity Scene::createEntity(const std::string& name)
	{
		Entity result = { this->m_Registry.create(), this };
		result.addComponent<TagComponent>(name);
		result.addComponent<TransformComponent>();
		return result;
	}
	Entity Scene::createEntity(CONST_REF(uint32_t) hint, const std::string& name)
	{
		Entity result = { this->m_Registry.create(static_cast<entt::registry::entity_type>(hint)), this };
		result.addComponent<TagComponent>(name);
		result.addComponent<TransformComponent>();
		return result;
	}
	void Scene::onEvent(const events::Event& event)
	{
		this->m_Registry.view<scene::CameraComponent>().each([&](auto entityID, auto& udc)
			{
				udc.setViewMatrix(Entity(entityID, this).getComponent<scene::TransformComponent>().toMatrix());
				if (udc.m_Primary)
				{
					this->setActiveCamera(udc.m_Camera.m_Projection);
				}
			});
		this->m_Registry.view<scene::NativeScriptComponent>().each([&](auto entity, auto& nsc)
			{
				if (nsc.m_Instance)
				{
					nsc.m_Instance->onEvent(event);
				}
			});
	}
	void Scene::onViewportResized(float width, float height)
	{
		this->m_Registry.view<scene::CameraComponent>().each([&](auto entityID, auto& udc)
			{
				udc.setViewportSize(width, height);
			});
	}
	template<typename T>
	void Scene::onComponentAdded(const Entity&, T& component)
	{
		static_assert(false);
	}
	template<>
	void Scene::onComponentAdded<TagComponent>(const Entity&, TagComponent& component) {}
	template<>
	void Scene::onComponentAdded<TransformComponent>(const Entity&, TransformComponent& component) {}
	template<>
	void Scene::onComponentAdded<CameraComponent>(const Entity&, CameraComponent& component) {}
	template<>
	void Scene::onComponentAdded<MeshComponent>(const Entity&, MeshComponent& component) {}
	template<>
	void Scene::onComponentAdded<MaterialComponent>(const Entity&, MaterialComponent& component) {}
	template<>
	void Scene::onComponentAdded<NativeScriptComponent>(const Entity&, NativeScriptComponent& component) {}
}
