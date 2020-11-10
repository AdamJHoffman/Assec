#pragma once

#include "core/Base.h"

#include "event/Event.h"

#include "transactions/Transaction.h"

namespace assec::layersystem
{
	const class Layer
	{
	public:
		Layer(bool enabled = true) : m_Enabled(enabled) { TIME_FUNCTION; }
		~Layer() { TIME_FUNCTION; }
		virtual void onEvent(const events::Event& event) = 0;
		virtual void onTransaction(const transactions::Transaction& event) = 0;
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		bool m_Enabled;
	private:
	};
}
