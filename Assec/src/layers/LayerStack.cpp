#include "acpch.h"
#include "LayerStack.h"

namespace assec::layersystem
{
	LayerStack::LayerStack() : m_Layers(std::vector<ref<Layer>>()), m_LayerInsertIndex(0) { TIME_FUNCTION; }
	LayerStack::~LayerStack()
	{
		TIME_FUNCTION;
		for (ref<Layer> layer : this->m_Layers)
		{
			layer->onDetach();
		}
	}
	void LayerStack::addLayer(ref<Layer> layer)
	{
		TIME_FUNCTION;
		this->m_Layers.emplace(this->m_Layers.begin() + this->m_LayerInsertIndex, layer);
		this->m_LayerInsertIndex++;
		if (layer->m_Enabled)
		{
			layer->onAttach();
		}
	}
	void LayerStack::addOverlay(ref<Layer> layer)
	{
		TIME_FUNCTION;
		this->m_Layers.emplace_back(layer);
		if (layer->m_Enabled)
		{
			layer->onAttach();
		}
	}
	void LayerStack::removeLayer(ref<Layer> layer)
	{
		TIME_FUNCTION;
		auto found = std::find(this->m_Layers.begin(), this->m_Layers.end(), layer);
		if (found != this->m_Layers.end())
		{
			this->m_Layers.erase(found);
			this->m_LayerInsertIndex--;
			if (layer->m_Enabled)
			{
				layer->onDetach();
			}
		}
	}
	void LayerStack::removeOverlay(ref<Layer> layer)
	{
		TIME_FUNCTION;
		auto found = std::find(this->m_Layers.begin(), this->m_Layers.end(), layer);
		if (found != this->m_Layers.end())
		{
			this->m_Layers.erase(found);
			if (layer->m_Enabled)
			{
				layer->onDetach();
			}
		}
	}
	void LayerStack::onEvent(const events::Event& event) const
	{
		TIME_FUNCTION;
		for (auto layer : this->m_Layers)
		{
			if (layer->m_Enabled)
			{
				layer->onEvent(event);
			}
		}
	}
}
