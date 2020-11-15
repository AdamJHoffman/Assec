#include "acpch.h"

#include "Transaction.h"

namespace assec::transactions
{
	void TransactionQueue::addTransaction(const ref<Transaction>& action)
	{
		m_TransactionQueue.push_back(action);
	}
	void TransactionQueue::submit(ref<Transaction>& transaction)
	{
		this->m_TransactionQueue.push_back(transaction);
	}
	void TransactionQueue::clear()
	{
		this->m_TransactionQueue.clear();
	}
	ref<Transaction> EntityRemovalTransaction::generateInverse()
	{
		auto& data = this->m_RemovedData;
		auto& result = makeRef<EntityCreationTransaction>(this->m_Removed, [data](scene::Entity& created)
			{
				created.getComponent<scene::TagComponent>() = data.m_TagComponent;
				created.getComponent<scene::TransformComponent>() = data.m_TransformComponent;
			});
		return result;
	}
	ref<Transaction> EntityCreationTransaction::generateInverse()
	{
		if (this->m_Created)
		{
			return makeRef<EntityRemovalTransaction>(this->m_Created);
		}
		return nullptr;
	}
	template<typename T>
	ref<Transaction> ComponentRemovalTransaction<T>::generateInverse()
	{
		return makeRef<ComponentCreationTransaction<T>>(this->m_Entity, this->m_Removed);
	}
	template<typename T>
	ref<Transaction> ComponentCreationTransaction<T>::generateInverse()
	{
		return makeRef<ComponentRemovalTransaction<T>>(this->m_Entity);
	}

	template class ComponentRemovalTransaction<scene::TagComponent>;
	template class ComponentRemovalTransaction<scene::TransformComponent>;
	template class ComponentRemovalTransaction<scene::NativeScriptComponent>;
	template class ComponentRemovalTransaction<scene::MeshComponent>;
	template class ComponentRemovalTransaction<scene::MaterialComponent>;
	template class ComponentRemovalTransaction<scene::CameraComponent>;

	template class ComponentCreationTransaction<scene::TagComponent>;
	template class ComponentCreationTransaction<scene::TransformComponent>;
	template class ComponentCreationTransaction<scene::NativeScriptComponent>;
	template class ComponentCreationTransaction<scene::MeshComponent>;
	template class ComponentCreationTransaction<scene::MaterialComponent>;
	template class ComponentCreationTransaction<scene::CameraComponent>;
}