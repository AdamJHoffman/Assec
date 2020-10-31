#include "acpch.h"
#include "Scene.h"
#include "Components.h"
#include "event/EngineEvents.h"
#include "core/Application.h"

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
	void Scene::onEvent(const events::Event& event)
	{
		this->m_Registry.view<scene::CameraComponent>().each([&](auto entity, auto& udc)
			{
				udc.onEvent(event);
				if (udc.m_Primary)
				{
					this->m_ActiveCamera = &udc.m_Camera.m_Projection;
				}
			});
		this->m_Registry.view<scene::NativeScriptComponent>().each([&](auto entity, auto& nsc)
			{
				if (!nsc.m_Instance)
				{
					nsc.m_InstantiateFunction(entity, this);
				}
				nsc.onEvent(event);
			});
	}
}
