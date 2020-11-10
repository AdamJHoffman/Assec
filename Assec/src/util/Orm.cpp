#include "acpch.h"

#include "Orm.h"

namespace assec::util
{
	AbstractOrmField::AbstractOrmField(const Access& access) : m_Access(access) {}
	AbstractOrmField::~AbstractOrmField() {}
	const Access& AbstractOrmField::getAccess() const { return this->m_Access; }
	const std::string& AbstractOrmField::getType() const { return this->m_Type; }

	FieldDispatcher::FieldDispatcher(const AbstractOrmField& field) : m_Field(*const_cast<AbstractOrmField*>(&field)) {}

	BaseOrm::BaseOrm() {}
	BaseOrm::~BaseOrm()
	{
		auto& values = util::Values(this->m_Fields);
		for (auto& value : values)
		{
			delete value;
		}
	}
	
	const std::map<std::string, AbstractOrmField*>& BaseOrm::getFields()
	{
		return this->m_Fields;
	}
}