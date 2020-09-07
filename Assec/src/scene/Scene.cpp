#include "acpch.h"
#include "Scene.h"
#include "Components.h"
#include "event/EngineEvents.h"
#include "core/Application.h"

namespace assec::scene
{
	Scene::Scene() {}
	Scene::~Scene() {}
	Entity Scene::createEntity(const char* name)
	{
		Entity result = { this->m_Registry.create(), this };
		result.addComponent<TagComponent>(name);
		result.addComponent<TransformComponent>();
		return result;
	}
	void Scene::onEvent(const events::Event& event)
	{
		this->m_Registry.view<scene::OrthoCameraComponent>().each([&](auto entity, auto& udc)
			{
				udc.onEvent(event);
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
	void Scene::setActiveCamera(glm::mat4& camera)
	{
		this->m_ActiveCamera = &camera;
	}

}
