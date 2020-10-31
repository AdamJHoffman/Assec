#pragma once

#include "event/Event.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"

namespace assec
{
	class Input
	{
	public:
		static void onEvent(const events::Event& event);
		static bool isKeyDown(const KEY& keycode);
		static bool isMouseButtonDown(const KEY& button);
		static bool m_Keys[500];
		static bool m_MouseButtons[9];
	private:
		Input() {}
		~Input() {}
	};
}
