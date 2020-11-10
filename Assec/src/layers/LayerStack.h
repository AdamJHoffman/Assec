#pragma once
#include "Layer.h"

#include "transactions/Transaction.h"

namespace assec::layersystem
{
	const class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		inline const std::vector<ref<Layer>>& getLayers() { TIME_FUNCTION; return this->m_Layers; }
		void addLayer(ref<Layer> layer);
		void removeLayer(ref<Layer> layer);
		void addOverlay(ref<Layer> layer);
		void removeOverlay(ref<Layer> layer);
		void onEvent(const events::Event& event);
		void onTransaction(const transactions::Transaction& event);
	private:
		std::vector<ref<Layer>> m_Layers = std::vector<ref<Layer>>();
		uint32_t m_LayerInsertIndex = 0;
	};
}
