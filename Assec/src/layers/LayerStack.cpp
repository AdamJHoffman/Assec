#include "acpch.h"
#include "LayerStack.h"

namespace assec::layersystem
{
	LayerStack::LayerStack() : m_Layers(std::vector<ref<Layer>>()), m_LayerInsertIndex(0) {}
	LayerStack::~LayerStack() {}
	void LayerStack::addLayer(ref<Layer> layer)
	{
		this->m_Layers.emplace(this->m_Layers.begin() + this->m_LayerInsertIndex, layer);
		this->m_LayerInsertIndex++;
		layer->onAttach();
	}
	void LayerStack::addOverlay(ref<Layer> layer)
	{
		this->m_Layers.emplace_back(layer);
		layer->onAttach();
	}
	void LayerStack::removeLayer(ref<Layer> layer)
	{
		auto found = std::find(this->m_Layers.begin(), this->m_Layers.end(), layer);
		if (found != this->m_Layers.end())
		{
			this->m_Layers.erase(found);
			this->m_LayerInsertIndex--;
			layer->onDetach();
		}
	}
	void LayerStack::removeOverlay(ref<Layer> layer)
	{
		auto found = std::find(this->m_Layers.begin(), this->m_Layers.end(), layer);
		if (found != this->m_Layers.end())
		{
			this->m_Layers.erase(found);
			layer->onDetach();
		}
	}
	void LayerStack::onEvent(events::Event& event) const
	{
		for (auto layer : this->m_Layers)
		{
			layer->onEvent(event);
		}
	}
}
