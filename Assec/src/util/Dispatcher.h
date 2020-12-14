#pragma once

#include "core/Base.h"

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
	private:
		T& m_Object;
	};
}