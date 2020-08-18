#include "acpch.h"
#include "Scene.h"

namespace assec::scene
{
	Scene::Scene() {}
	Scene::~Scene() {}
	const Entity Scene::createEntity()
	{
		return { this->m_Registry.create(), this };
	}
	void Scene::setActiveCamera(glm::mat4& camera)
	{
		this->m_ActiveCamera = &camera;
	}

}
