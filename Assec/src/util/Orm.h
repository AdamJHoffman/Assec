#pragma once

#include <map>
#include <string>
#include <typeinfo>

namespace assec::util
{
	enum class Access
	{
		PUBLIC = 0,
		PROTECTED,
		PRIVATE
	};

	struct AbstractOrmField
	{
		AbstractOrmField(const Access& access) : m_Access(access) {}
		virtual ~AbstractOrmField() {}
		const Access& getAccess() const { return this->m_Access; }
		const std::string& getType() const { return this->m_Type; }

	protected:
		Access m_Access;
		std::string m_Type;
	};

	template<typename T>
	class OrmField : public AbstractOrmField
	{
	public:
		OrmField(const Access& access, const T& value) : AbstractOrmField(access), m_Value(value)
		{
			this->m_Type = typeid(T).name();
		}
		OrmField() : AbstractOrmField(util::Access::PRIVATE) 
		{
			this->m_Type = "none";
		}
		~OrmField() {}
		const T& getValue() const { return this->m_Value; }
		T& getValue() { return this->m_Value; }
	private:
		T m_Value = T();
	};

	class FieldDispatcher
	{
		template<typename T> using FieldFn = std::function<void(T&)>;
	public:
		FieldDispatcher(const AbstractOrmField& field) : m_Field(*const_cast<AbstractOrmField*>(&field)) {}

		template<typename T> void dispatch(FieldFn<T> function)
		{
			TIME_FUNCTION;
			if (this->m_Field.getType() == typeid(T).name())
			{
				function((*(OrmField<T>*) & this->m_Field).getValue());
			}
		}
	private:
		AbstractOrmField& m_Field;
	};

	class BaseOrm
	{
	public:
		BaseOrm() {}
		~BaseOrm()
		{
			auto& values = util::Values(this->m_Fields);
			for (auto& value : values)
			{
				delete value;
			}
		}
		template<typename T>
		const OrmField<T>& addField(const std::string& name, OrmField<T>* field)
		{
			this->m_Fields.emplace(name, field);
			return *field;
		}
		template<typename T>
		const OrmField<T>& getField(const std::string& name) const
		{
			return *((OrmField<T>*)((void*)this->m_Fields.at(name)));
		}
		const std::map<std::string, AbstractOrmField*>& getFields()
		{
			return this->m_Fields;
		}
	private:
		std::map<std::string, AbstractOrmField*> m_Fields = std::map<std::string, AbstractOrmField*>();
	};
}
