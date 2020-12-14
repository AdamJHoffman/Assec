#pragma once

#include "core/Base.h"

#include "event/Event.h"

namespace assec::layersystem
{
	const class Layer
	{
	public:
		Layer(CONST_REF(bool) enabled = true) : m_Enabled(enabled) { TIME_FUNCTION; }
		~Layer() { TIME_FUNCTION; }
		virtual void onEvent(CONST_REF(events::Event) event) = 0;
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		INLINE CONST_REF(bool) enabled() const { TIME_FUNCTION; return this->m_Enabled; }
	private:
		bool m_Enabled;
	};
} // namespace assec::layersystem
