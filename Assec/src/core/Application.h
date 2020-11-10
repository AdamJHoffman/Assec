#pragma once
#include "event/EventQueue.h"

#include "layers/LayerStack.h"

#include "scene/Scene.h"

#include "transactions/Transaction.h"

namespace assec
{
	class Application
	{
	public:
		Application(const std::string name = "Assec");
		virtual ~Application();
		void onEvent(ref<events::Event> event);
		void onTransaction(ref<transactions::Transaction>);
		void handleEvents();
		void handleTransactions();
		void run();
		void close();
		virtual void init() = 0;
		ref<layersystem::LayerStack> AC_LAYER_STACK = std::make_shared<layersystem::LayerStack>();
		ref<events::EventQueue> AC_EVENT_QUEUE = std::make_shared<events::EventQueue>();
		ref<transactions::TransactionQueue> AC_TRANSACTION_QUEUE = std::make_shared<transactions::TransactionQueue>();
		ref<transactions::TransactionQueue> AC_TRANSACTION_ARCHIVE = std::make_shared<transactions::TransactionQueue>();
		ref<scene::Scene> m_ActiveScene = std::make_shared<scene::Scene>();
	private:
		bool m_ShouldClose = false;
		void cleanup() const;
	};
} // namespace assec
