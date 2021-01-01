#pragma once

#include <entt/entt.hpp>

#include "scene/Entity.h"
#include "scene/Components.h"

#include "core/Base.h"

#include "util/UUID.h"

namespace assec::transactions
{
	class Transaction
	{
	public:
		Transaction() = default;
		virtual ~Transaction() = default;
		virtual std::string toString() = 0;
		virtual ref<Transaction> generateInverse() = 0;
	};

	class TransactionQueue
	{
	public:
		TransactionQueue() = default;
		~TransactionQueue() = default;
		void addTransaction(const ref<Transaction>& action);
		void submit(ref<Transaction>&);
		void clear();
		INLINE REF(std::vector<ref<Transaction>>) getTransactionqueue()
		{
			return this->m_TransactionQueue;
		}
	private:
		std::vector<ref<Transaction>> m_TransactionQueue;
	};

	template<typename T>
	class RemovalTransaction : public Transaction
	{
	public:
		RemovalTransaction() = default;
		RemovalTransaction(CONST_REF(T) removed) : m_Removed(removed) {}
		virtual ~RemovalTransaction() {}
		std::string toString() override { return std::string("Transaction of type: ") + std::string(typeid(*this).name()); }
		INLINE CONST_REF(T) getRemoved() const { return this->m_Removed; }
	protected:
		T m_Removed;
	};

	template<typename T>
	class CreationTransaction : public Transaction
	{
	public:
		CreationTransaction(CONST_REF(std::function<void(T&)>) onCreateFunction = std::function<void(T&)>()) 
			: m_OnCreateFunction(onCreateFunction) {}
		CreationTransaction(CONST_REF(T) created, CONST_REF(std::function<void(T&)>) onCreateFunction = std::function<void(T&)>())
			: m_Created(created), m_OnCreateFunction(onCreateFunction) {}
		virtual ~CreationTransaction() = default;
		std::string toString() override { return std::string("Transaction of type: ") + std::string(typeid(*this).name()); }
		INLINE CONST_REF(T) getCreated() const { return this->m_Created;  }
		INLINE void setCreated(CONST_REF(T) created) const
		{ 
			this->m_Created = created;
			if (this->m_OnCreateFunction)
			{
				this->m_OnCreateFunction(this->m_Created);
			}
		}
		std::function<void(T&)> m_OnCreateFunction;
	protected:
		mutable T m_Created;
	};

	struct EntityData
	{
		scene::TagComponent m_TagComponent;
		scene::TransformComponent m_TransformComponent;
	};

	class EntityRemovalTransaction : public RemovalTransaction<scene::Entity>
	{
	public:
		EntityRemovalTransaction(CONST_REF(scene::Entity) entity) : RemovalTransaction<scene::Entity>(entity) 
		{
			this->m_RemovedData.m_TagComponent = entity.getComponent<scene::TagComponent>();
			this->m_RemovedData.m_TransformComponent = entity.getComponent<scene::TransformComponent>();
		}
		~EntityRemovalTransaction() = default;
		ref<Transaction> generateInverse() override;
	private:
		EntityData m_RemovedData;
	};


	class EntityCreationTransaction : public CreationTransaction<scene::Entity>
	{
	public:
		EntityCreationTransaction() = default;
		EntityCreationTransaction(CONST_REF(std::function<void(scene::Entity&)>) onCreateFunction)
			: CreationTransaction<scene::Entity>(onCreateFunction) {}
		EntityCreationTransaction(CONST_REF(scene::Entity) hint, CONST_REF(std::function<void(scene::Entity&)>) onCreateFunction) 
			: CreationTransaction<scene::Entity>(onCreateFunction), m_Hint(hint) {}
		~EntityCreationTransaction() = default;

		INLINE CONST_REF(scene::Entity) getHint() const { return this->m_Hint; }

		ref<Transaction> generateInverse() override;
	private:
		scene::Entity m_Hint = scene::Entity(static_cast<entt::entity>(uuid::generateUUID()), nullptr);
	};

	template<typename T>
	class ComponentRemovalTransaction : public RemovalTransaction<T>
	{
	public:
		ComponentRemovalTransaction(const scene::Entity& entity) : RemovalTransaction<T>(entity.getComponent<T>()), m_Entity(entity) {}
		~ComponentRemovalTransaction() = default;
		ref<Transaction> generateInverse() override;
		INLINE CONST_REF(scene::Entity) getEntity() const { return this->m_Entity; }
	private:
		scene::Entity m_Entity;
	};

	template<typename T>
	class ComponentCreationTransaction : public CreationTransaction<T>
	{
	public:
		ComponentCreationTransaction(const scene::Entity& entity) : m_Entity(entity) {}
		ComponentCreationTransaction(const scene::Entity& entity, CONST_REF(T) preset) : m_Entity(entity), CreationTransaction<T>(preset) {}
		ComponentCreationTransaction(const scene::Entity& entity, const std::function<void(T&)>& onComponetAdded)
			: m_Entity(entity), CreationTransaction<T>(T(), onComponetAdded) {}
		ComponentCreationTransaction(const scene::Entity& entity, CONST_REF(T) preset, const std::function<void(T&)>& onComponetAdded)
			: m_Entity(entity), CreationTransaction<T>(preset, onComponetAdded) {}
		~ComponentCreationTransaction() = default;
		ref<Transaction> generateInverse() override;
		INLINE CONST_REF(scene::Entity) getEntity() const { return this->m_Entity; }
	private:
		scene::Entity m_Entity;
	};

	class AbstractValueChangedTransaction : public Transaction
	{
	public:
		AbstractValueChangedTransaction() = default;
		~AbstractValueChangedTransaction() = default;
		virtual void changeValue() const = 0;
		virtual std::string toString() override
		{
			return std::string("Transaction of type: ") + std::string(typeid(*this).name());
		}
	};

	template<typename T>
	class ValueChangedTransaction : public AbstractValueChangedTransaction
	{
	public:
		ValueChangedTransaction(T* variable, const T& value) : m_Variable(variable), m_OriginalValue(*m_Variable), m_Value(value) {}
		ValueChangedTransaction(T* variable, const T& value, const std::function<void(T&)>& onValueChanged)
			: m_Variable(variable), m_OriginalValue(*m_Variable), m_Value(value), m_OnValueChanged(onValueChanged) {}
		~ValueChangedTransaction() = default;
		ref<Transaction> generateInverse() override
		{
			return makeRef<ValueChangedTransaction<T>>(this->m_Variable, this->m_OriginalValue);
		}
		void changeValue() const override
		{
			*this->m_Variable = this->m_Value;
			if (this->m_OnValueChanged)
			{
				this->m_OnValueChanged(*this->m_Variable);
			}
		}
	private:
		mutable T* m_Variable = nullptr;
		T m_OriginalValue;
		T m_Value;
		std::function<void(T&)> m_OnValueChanged;
	};

	class Dispatcher
	{
		template<typename T> using TransactionFn = std::function<void(const T&)>;
	public:
		Dispatcher(const Transaction& event) : m_Transaction(*const_cast<Transaction*>(&event)) {}

		template<typename T> void dispatch(TransactionFn<T> function)
		{
			TIME_FUNCTION;
			if (typeid(m_Transaction) == typeid(T) || dynamic_cast<T*>(&m_Transaction) != nullptr)
			{
				function(*(T*)&m_Transaction);
			}
		}
	private:
		Transaction& m_Transaction;
	};
}