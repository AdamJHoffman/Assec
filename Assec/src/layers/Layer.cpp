#include "acpch.h"
#include "Layer.h"

namespace assec::layersystem
{
	Layer::Layer(bool enabled) : m_GameObjects(std::vector<ref<GameObject>>()), m_Enabled(enabled) {}
	Layer::~Layer() {}
	void Layer::onEvent(events::Event& event) const
	{
		if (this->m_Enabled)
		{
			events::Dispatcher dispatcher = events::Dispatcher(event);
			for (auto object : this->m_GameObjects)
			{
				if (object->m_Enabled)
				{
					// function for every event
				}
			}
		}
	}
	void Layer::onAttach() {}
	void Layer::onDetach() {}
}
