#include "acpch.h"

#include "Scene.h"
#include "Components.h"

#include "core/Application.h"

#include "graphics/WindowManager.h"

#include "event/EngineEvents.h"

#include "transactions/Transaction.h"

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
				udc.onEvent(event);
				udc.setViewMatrix(Entity(entityID, this).getComponent<scene::TransformComponent>().toMatrix());
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
					nsc.m_Instance->onEvent(event);
				}
			});
	}
	void Scene::onTransaction(const transactions::Transaction& transaction)
	{
		transactions::Dispatcher dispatcher = transactions::Dispatcher(transaction);
		dispatcher.dispatch<transactions::EntityCreationTransaction>([&](const transactions::EntityCreationTransaction& creationTransaction)
			{
				creationTransaction.setCreated(this->createEntity(creationTransaction.getHint().getNative()));
			});
		dispatcher.dispatch<transactions::EntityRemovalTransaction>([&](const transactions::EntityRemovalTransaction& removalTransaction)
			{
				this->m_Registry.destroy(static_cast<entt::entity>(removalTransaction.getRemoved().getNative()));
			});

		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::TagComponent>>([&](const transactions::ComponentRemovalTransaction<scene::TagComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent<TagComponent>();
			});
		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::TransformComponent>>([&](const transactions::ComponentRemovalTransaction<scene::TransformComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent<TransformComponent>();
			});
		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::CameraComponent>>([&](const transactions::ComponentRemovalTransaction<scene::CameraComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent<CameraComponent>();
			});
		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::MeshComponent>>([&](const transactions::ComponentRemovalTransaction<scene::MeshComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent<MeshComponent>();
			});
		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::MaterialComponent>>([&](const transactions::ComponentRemovalTransaction<scene::MaterialComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent<MaterialComponent>();
			});
		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::NativeScriptComponent>>([&](const transactions::ComponentRemovalTransaction<scene::NativeScriptComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent<NativeScriptComponent>();
			});

		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::TagComponent>>([&](const transactions::ComponentCreationTransaction<scene::TagComponent>& removalTransaction)
			{
				auto& component = removalTransaction.getEntity().addComponent<TagComponent>(removalTransaction.getCreated());
				if (removalTransaction.m_OnCreateFunction)
				{
					removalTransaction.m_OnCreateFunction(component);
				}
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::TransformComponent>>([&](const transactions::ComponentCreationTransaction<scene::TransformComponent>& removalTransaction)
			{
				auto& component = removalTransaction.getEntity().addComponent<TransformComponent>(removalTransaction.getCreated());
				if (removalTransaction.m_OnCreateFunction)
				{
					removalTransaction.m_OnCreateFunction(component);
				}
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::CameraComponent>>([&](const transactions::ComponentCreationTransaction<scene::CameraComponent>& removalTransaction)
			{
				auto& component = removalTransaction.getEntity().addComponent<CameraComponent>(removalTransaction.getCreated());
				if (removalTransaction.m_OnCreateFunction)
				{
					removalTransaction.m_OnCreateFunction(component);
				}
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::MeshComponent>>([&](const transactions::ComponentCreationTransaction<scene::MeshComponent>& removalTransaction)
			{
				auto& component = removalTransaction.getEntity().addComponent<MeshComponent>(removalTransaction.getCreated());
				if (removalTransaction.m_OnCreateFunction)
				{
					removalTransaction.m_OnCreateFunction(component);
				}
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::MaterialComponent>>([&](const transactions::ComponentCreationTransaction<scene::MaterialComponent>& removalTransaction)
			{
				auto& component = removalTransaction.getEntity().addComponent<MaterialComponent>(removalTransaction.getCreated());
				if (removalTransaction.m_OnCreateFunction)
				{
					removalTransaction.m_OnCreateFunction(component);
				}
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::NativeScriptComponent>>([&](const transactions::ComponentCreationTransaction<scene::NativeScriptComponent>& removalTransaction)
			{
				auto& component = removalTransaction.getEntity().addComponent<NativeScriptComponent>(removalTransaction.getCreated());
				if (removalTransaction.m_OnCreateFunction)
				{
					removalTransaction.m_OnCreateFunction(component);
				}
			});
	}
	void Scene::setTransactionCallback(const std::function<void(ref<transactions::Transaction>)>& transactionCallback)
	{
		this->m_TransactionCallback = transactionCallback;
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
