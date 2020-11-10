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
				this->createEntity();
			});
		dispatcher.dispatch<transactions::EntityRemovalTransaction>([&](const transactions::EntityRemovalTransaction& removalTransaction)
			{
				this->m_Registry.destroy(static_cast<entt::entity>(removalTransaction.getNative()));
			});

		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::TagComponent>>([&](const transactions::ComponentRemovalTransaction<scene::TagComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent< TagComponent>();
			});
		dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::TransformComponent>>([&](const transactions::ComponentRemovalTransaction<scene::TransformComponent>& removalTransaction)
			{
				removalTransaction.getEntity().removeComponent< TransformComponent>();
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
				if (removalTransaction.m_OnComponetAdded)
				{
					removalTransaction.m_OnComponetAdded(removalTransaction.getEntity().addComponent<TagComponent>());
					return;
				}
				removalTransaction.getEntity().addComponent<TagComponent>();
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::TransformComponent>>([&](const transactions::ComponentCreationTransaction<scene::TransformComponent>& removalTransaction)
			{
				if (removalTransaction.m_OnComponetAdded)
				{
					removalTransaction.m_OnComponetAdded(removalTransaction.getEntity().addComponent<TransformComponent>());
					return;
				}
				removalTransaction.getEntity().addComponent<TransformComponent>();
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::CameraComponent>>([&](const transactions::ComponentCreationTransaction<scene::CameraComponent>& removalTransaction)
			{
				if (removalTransaction.m_OnComponetAdded)
				{
					removalTransaction.m_OnComponetAdded(removalTransaction.getEntity().addComponent<CameraComponent>());
					return;
				}
				removalTransaction.getEntity().addComponent<CameraComponent>();
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::MeshComponent>>([&](const transactions::ComponentCreationTransaction<scene::MeshComponent>& removalTransaction)
			{
				if (removalTransaction.m_OnComponetAdded)
				{
					removalTransaction.m_OnComponetAdded(removalTransaction.getEntity().addComponent<MeshComponent>());
					return;
				}
				removalTransaction.getEntity().addComponent<MeshComponent>();
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::MaterialComponent>>([&](const transactions::ComponentCreationTransaction<scene::MaterialComponent>& removalTransaction)
			{
				if (removalTransaction.m_OnComponetAdded)
				{
					removalTransaction.m_OnComponetAdded(removalTransaction.getEntity().addComponent<MaterialComponent>());
					return;
				}
				removalTransaction.getEntity().addComponent<MaterialComponent>();
			});
		dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::NativeScriptComponent>>([&](const transactions::ComponentCreationTransaction<scene::NativeScriptComponent>& removalTransaction)
			{
				if (removalTransaction.m_OnComponetAdded)
				{
					removalTransaction.m_OnComponetAdded(removalTransaction.getEntity().addComponent<NativeScriptComponent>());
					return;
				}
				removalTransaction.getEntity().addComponent<NativeScriptComponent>();
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
