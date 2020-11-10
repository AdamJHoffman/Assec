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
	EntityRemovalTransaction::EntityRemovalTransaction(const uint32_t& id) : m_ID(id) {}
	CONST_REF(uint32_t) EntityRemovalTransaction::getNative() const
	{
		return this->m_ID;
	}
	ref<Transaction> EntityRemovalTransaction::generateInverse()
	{
		return makeRef<EntityCreationTransaction>();
	}
	void EntityCreationTransaction::setCreated(CONST_REF(scene::Entity) entity)
	{
		this->m_Created = entity;
	}
	ref<Transaction> EntityCreationTransaction::generateInverse()
	{
		if (this->m_Created)
		{
			return makeRef<EntityRemovalTransaction>(this->m_Created);
		}
		return nullptr;
	}

}