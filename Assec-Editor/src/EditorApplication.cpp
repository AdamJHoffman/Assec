#include "EditorApplication.h"

#include "include/Assec.h"

#include "EditorLayer.h"
#include "EditorGuiLayer.h"

namespace assec::editor
{
	EditorApplication::EditorApplication() {}
	EditorApplication::~EditorApplication() {}
	void EditorApplication::init()
	{
		this->m_FrameBuffer = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createFrameBuffer({ {}, 1920, 1080, 1, false, });
		this->m_FrameBuffer->addTextureAttachment(Type::COLOR_ATTACHMENT0, Type::RGBA8, Type::RGBA, Type::UNSIGNED_BYTE);
		this->m_FrameBuffer->addTextureAttachment(Type::DEPTH_STENCIL_ATTACHMENT, Type::DEPTH24_STENCIL8, Type::DEPTH_STENCIL, Type::UNSIGNED_INT_24_8);
		this->m_FrameBuffer->validate();
		this->AC_LAYER_STACK->addLayer(std::make_shared<EditorLayer>(*this));
		this->AC_LAYER_STACK->addOverlay(std::make_shared<EditorGuiLayer>(*this));
		graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->setClearColor(glm::vec4(0.09803921568, 0.09803921568, 0.11764705882, 1.0f));
		graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->enable(Type::DEPTH_TEST);
		graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->setDepthFunction(Type::LESS);
	}
	void EditorApplication::frame()
	{
		this->handleTransactions();
	}
	void EditorApplication::onTransaction(ref<transactions::Transaction> transaction)
	{
		TIME_FUNCTION;
		this->AC_TRANSACTION_QUEUE->submit(transaction);
		this->AC_TRANSACTION_ARCHIVE->submit(transaction);
		this->AC_TRANSACTION_REDO_ARCHIVE->getTransactionqueue().clear();
	}
	void EditorApplication::handleTransactions()
	{
		TIME_FUNCTION;
		auto tempQueue = this->AC_TRANSACTION_QUEUE->getTransactionqueue();
		size_t size = tempQueue.size();
		if (size > 0 && graphics::WindowManager::getMainWindow().getWindowData().m_Title.back() != '*')
		{
			graphics::WindowManager::getMainWindow().setTitle((graphics::WindowManager::getMainWindow().getWindowData().m_Title + std::string("*")).c_str());
		}
		for (size_t i = 0; i < size; i++)
		{
			auto& transaction = tempQueue[i];
			AC_CORE_TRACE(transaction->toString());
			transactions::Dispatcher dispatcher = transactions::Dispatcher(*transaction);
			dispatcher.dispatch<transactions::AbstractValueChangedTransaction>([](const transactions::AbstractValueChangedTransaction& valueChanged)
				{
					valueChanged.changeValue();
				});
			dispatcher.dispatch<transactions::EntityCreationTransaction>([&](const transactions::EntityCreationTransaction& creationTransaction)
				{
					creationTransaction.setCreated(this->m_ActiveScene->createEntity(creationTransaction.getHint().getNative()));
				});
			dispatcher.dispatch<transactions::EntityRemovalTransaction>([&](const transactions::EntityRemovalTransaction& removalTransaction)
				{
					this->m_ActiveScene->reg().destroy(static_cast<entt::entity>(removalTransaction.getRemoved().getNative()));
				});

			dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::TagComponent>>([&](const transactions::ComponentRemovalTransaction<scene::TagComponent>& removalTransaction)
				{
					removalTransaction.getEntity().removeComponent<scene::TagComponent >();
				});
			dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::TransformComponent>>([&](const transactions::ComponentRemovalTransaction<scene::TransformComponent>& removalTransaction)
				{
					removalTransaction.getEntity().removeComponent<scene::TransformComponent>();
				});
			dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::CameraComponent>>([&](const transactions::ComponentRemovalTransaction<scene::CameraComponent>& removalTransaction)
				{
					removalTransaction.getEntity().removeComponent<scene::CameraComponent>();
				});
			dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::MeshComponent>>([&](const transactions::ComponentRemovalTransaction<scene::MeshComponent>& removalTransaction)
				{
					removalTransaction.getEntity().removeComponent<scene::MeshComponent>();
				});
			dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::MaterialComponent>>([&](const transactions::ComponentRemovalTransaction<scene::MaterialComponent>& removalTransaction)
				{
					removalTransaction.getEntity().removeComponent<scene::MaterialComponent>();
				});
			dispatcher.dispatch<transactions::ComponentRemovalTransaction<scene::NativeScriptComponent>>([&](const transactions::ComponentRemovalTransaction<scene::NativeScriptComponent>& removalTransaction)
				{
					removalTransaction.getEntity().removeComponent<scene::NativeScriptComponent>();
				});

			dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::TagComponent>>([&](const transactions::ComponentCreationTransaction<scene::TagComponent>& removalTransaction)
				{
					auto& component = removalTransaction.getEntity().addComponent<scene::TagComponent>(removalTransaction.getCreated());
					if (removalTransaction.m_OnCreateFunction)
					{
						removalTransaction.m_OnCreateFunction(component);
					}
				});
			dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::TransformComponent>>([&](const transactions::ComponentCreationTransaction<scene::TransformComponent>& removalTransaction)
				{
					auto& component = removalTransaction.getEntity().addComponent<scene::TransformComponent>(removalTransaction.getCreated());
					if (removalTransaction.m_OnCreateFunction)
					{
						removalTransaction.m_OnCreateFunction(component);
					}
				});
			dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::CameraComponent>>([&](const transactions::ComponentCreationTransaction<scene::CameraComponent>& removalTransaction)
				{
					auto& component = removalTransaction.getEntity().addComponent<scene::CameraComponent>(removalTransaction.getCreated());
					if (removalTransaction.m_OnCreateFunction)
					{
						removalTransaction.m_OnCreateFunction(component);
					}
				});
			dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::MeshComponent>>([&](const transactions::ComponentCreationTransaction<scene::MeshComponent>& removalTransaction)
				{
					auto& component = removalTransaction.getEntity().addComponent<scene::MeshComponent>(removalTransaction.getCreated());
					if (removalTransaction.m_OnCreateFunction)
					{
						removalTransaction.m_OnCreateFunction(component);
					}
				});
			dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::MaterialComponent>>([&](const transactions::ComponentCreationTransaction<scene::MaterialComponent>& removalTransaction)
				{
					auto& component = removalTransaction.getEntity().addComponent<scene::MaterialComponent>(removalTransaction.getCreated());
					if (removalTransaction.m_OnCreateFunction)
					{
						removalTransaction.m_OnCreateFunction(component);
					}
				});
			dispatcher.dispatch<transactions::ComponentCreationTransaction<scene::NativeScriptComponent>>([&](const transactions::ComponentCreationTransaction<scene::NativeScriptComponent>& removalTransaction)
				{
					auto& component = removalTransaction.getEntity().addComponent<scene::NativeScriptComponent>(removalTransaction.getCreated());
					if (removalTransaction.m_OnCreateFunction)
					{
						removalTransaction.m_OnCreateFunction(component);
					}
				});
		}
		this->AC_TRANSACTION_QUEUE->getTransactionqueue().erase(this->AC_TRANSACTION_QUEUE->getTransactionqueue().begin(), this->AC_TRANSACTION_QUEUE->getTransactionqueue().begin() + size);
	}
} // namespace assec::editor

int main()
{
	assec::editor::EditorApplication().run();
}
