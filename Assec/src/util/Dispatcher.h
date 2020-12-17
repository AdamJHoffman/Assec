#pragma once

#include "core/Base.h"

#include "event/Event.h"

namespace assec::util
{
	template<typename T>
	class Dispatcher
	{
		template<typename T> using function = std::function<void(const T&)>;
	public:
		Dispatcher(const T& object) : m_Object(*const_cast<T*>(&object)) {}

		template<typename T> void dispatch(function<T> function)
		{
			TIME_FUNCTION;
			if (typeid(m_Object) == typeid(T) || dynamic_cast<T*>(&m_Object) != nullptr)
			{
				function(*(T*)&m_Object);
			}
		}
	protected:
		T& m_Object;
	};

	class EventDispatcher : public Dispatcher<events::Event>
	{
		template<typename T> using function = std::function<bool(const T&)>;
	public:
		EventDispatcher(const events::Event& object) : Dispatcher(object) {}

		template<typename T> void dispatch(function<T> function)
		{
			TIME_FUNCTION;
			if (!this->m_Object.handled && (typeid(m_Object) == typeid(T) || dynamic_cast<T*>(&m_Object) != nullptr))
			{
				this->m_Object.handled = function(*(T*)&m_Object);
			}
		}
	};
}