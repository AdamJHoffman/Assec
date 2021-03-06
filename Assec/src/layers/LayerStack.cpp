﻿#include "acpch.h"

#include "LayerStack.h"

namespace assec::layersystem
{
	LayerStack::LayerStack() { TIME_FUNCTION; }
	LayerStack::~LayerStack()
	{
		TIME_FUNCTION;
		for (auto& layer : this->m_Layers)
		{
			layer->onDetach();
		}
	}
	void LayerStack::addLayer(ref<Layer> layer)
	{
		TIME_FUNCTION;
		this->m_Layers.emplace(this->m_Layers.begin() + this->m_LayerInsertIndex, layer);
		this->m_LayerInsertIndex++;
		if (layer->enabled())
		{
			layer->onAttach();
		}
	}
	void LayerStack::addOverlay(ref<Layer> layer)
	{
		TIME_FUNCTION;
		this->m_Layers.emplace_back(layer);
		if (layer->enabled())
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
			if (layer->enabled())
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
			if (layer->enabled())
			{
				layer->onDetach();
			}
		}
	}
	void LayerStack::onEvent(CONST_REF(events::Event) event)
	{
		TIME_FUNCTION;
		for (auto& layer : this->m_Layers)
		{
			if (layer->enabled())
			{
				layer->onEvent(event);
			}
		}
	}
} // namespace assec::layersystem
