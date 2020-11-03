#include "acpch.h"

#include "Scene.h"

#include "core/Application.h"

#include "graphics/WindowManager.h"

#include "Components.h"

#include "event/EngineEvents.h"

namespace assec::scene
{
	Scene::Scene() {}
	Scene::~Scene() {}
	Entity Scene::createEntity(const std::string& name)
	{
		Entity result = { this->m_Registry.create(), this };
		result.addComponent<TagComponent>(name);
		result.addComponent<TransformComponent>();
		return result;
	}
	void Scene::destroyEntity(const Entity& entity)
	{
		this->m_Registry.destroy(entity);
	}
	void Scene::onEvent(const ref<events::Event> event)
	{
		this->m_Registry.view<scene::CameraComponent>().each([&](auto entityID, auto& udc)
			{
				udc.onEvent(*event);
				Entity entity = Entity(entityID, this);
				udc.setViewMatrix(entity.getComponent<scene::TransformComponent>().toMatrix());
				if (udc.m_Primary)
				{
					this->m_ActiveCamera = udc.m_Camera.m_Projection;
				}
			});
		this->m_Registry.view<scene::NativeScriptComponent>().each([&](auto entity, auto& nsc)
			{
				if (!nsc.m_Instance)
				{
					nsc.m_Instance = nsc.InstantiateScript(entity, this);
				}
				if (nsc.m_Instance)
				{
					nsc.m_Instance->onEvent(*event);
				}
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
	void Scene::onComponentAdded<CameraComponent>(const Entity&, CameraComponent& component)
	{
		auto& size = graphics::WindowManager::getWindows()[0]->getSize();
		component.setViewportSize(static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y));
	}
	template<>
	void Scene::onComponentAdded<MeshComponent>(const Entity&, MeshComponent& component) {}
	template<>
	void Scene::onComponentAdded<MaterialComponent>(const Entity&, MaterialComponent& component) {}
	template<>
	void Scene::onComponentAdded<NativeScriptComponent>(const Entity&, NativeScriptComponent& component) {}
}
