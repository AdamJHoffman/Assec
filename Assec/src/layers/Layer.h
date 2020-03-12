#pragma once
#include "gameobjects/GameObject.h"
#include "core/Config.h"

namespace assec::layersystem
{
	const class Layer
	{
	public:
		Layer(bool enabled = true);
		~Layer();
		inline std::vector<ref<GameObject>>& getGameObjects() { return this->m_GameObjects; }
		void onEvent(events::Event& event);
		void onAttach();
		void onDetach();
		bool m_Enabled;
	private:
		std::vector<ref<GameObject>> m_GameObjects;
	};
}
