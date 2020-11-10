#pragma once

#include <entt/entt.hpp>

#include "scene/Entity.h"
#include "scene/Components.h"

#include "core/Base.h"

namespace assec::transactions
{
	class Transaction
	{
	public:
		Transaction() = default;
		virtual ~Transaction() = default;
		virtual std::string toString() = 0;
		virtual ref<Transaction> generateInverse() { return nullptr; };
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
		RemovalTransaction() {}
		virtual ~RemovalTransaction() {}
		std::string toString() override
		{
			return std::string("Transaction of type: ") + std::string(typeid(*this).name());
		}
	};

	template<typename T>
	class CreationTransaction : public Transaction
	{
	public:
		CreationTransaction() = default;
		virtual ~CreationTransaction() = default;
		std::string toString() override
		{
			return std::string("Transaction of type: ") + std::string(typeid(*this).name());
		}
		INLINE void setObject(const T& object) { this->m_Object = object; }
		INLINE T* getObject() { return this->m_Object; }
	private:
		T m_Object;
	};

	class EntityRemovalTransaction : public RemovalTransaction<uint32_t>
	{
	public:
		EntityRemovalTransaction(const uint32_t& id);
		~EntityRemovalTransaction() = default;
		CONST_REF(uint32_t) getNative() const;
		ref<Transaction> generateInverse() override;
	private:
		uint32_t m_ID;
	};


	class EntityCreationTransaction : public CreationTransaction<scene::Entity>
	{
	public:
		EntityCreationTransaction() = default;
		virtual ~EntityCreationTransaction() = default;
		void setCreated(CONST_REF(scene::Entity) entity);
		ref<Transaction> generateInverse() override;
	private:
		scene::Entity m_Created;
	};

	template<typename T>
	class ComponentRemovalTransaction : public RemovalTransaction<T>
	{
	public:
		ComponentRemovalTransaction(const scene::Entity& entity) : RemovalTransaction<T>(), m_Entity(entity) {}
		~ComponentRemovalTransaction() = default;
		const scene::Entity& getEntity() const
		{
			return this->m_Entity;
		}
	private:
		scene::Entity m_Entity;
	};

	template<typename T>
	class ComponentCreationTransaction : public CreationTransaction<T>
	{
	public:
		ComponentCreationTransaction(const scene::Entity& entity) : m_Entity(entity) {}
		ComponentCreationTransaction(const scene::Entity& entity, const std::function<void(T&)>& onComponetAdded) 
			: m_Entity(entity), m_OnComponetAdded(onComponetAdded) {}
		~ComponentCreationTransaction() = default;
		const scene::Entity& getEntity() const
		{
			return this->m_Entity;
		}
		std::function<void(T&)> m_OnComponetAdded;
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
		ValueChangedTransaction(T* variable, const T& value) : m_Variable(variable), m_Value(value) {}
		ValueChangedTransaction(T* variable, const T& value, const std::function<void(T&)>& onValueChanged)
			: m_Variable(variable), m_Value(value), m_OnValueChanged(onValueChanged) {}
		~ValueChangedTransaction() = default;
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