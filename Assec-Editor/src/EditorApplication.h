#pragma once
#include "include/Assec.h"

#include "transactions/Transaction.h"

#include "camera/EditorCamera.h"

namespace assec::editor
{
	enum class ApplicationState
	{
		EDITOR = 0,
		GAME
	};

	class EditorApplication : public assec::Application
	{
	public:
		EditorApplication();
		~EditorApplication();
		virtual void init0() override;
		virtual void run0() override;
		virtual void handleSceneEvents(CONST_REF(events::Event) event);
		virtual void onEvent0(ref<events::Event> event);
		void onTransaction(ref<transactions::Transaction>);
		void handleTransactions();


		ApplicationState m_CurrentState = ApplicationState::EDITOR;
		EditorCamera m_Camera = EditorCamera();
		ref<graphics::Framebuffer> m_FrameBuffer = nullptr;
		ref<transactions::TransactionQueue> AC_TRANSACTION_QUEUE = std::make_shared<transactions::TransactionQueue>();
		ref<transactions::TransactionQueue> AC_TRANSACTION_REDO_ARCHIVE = std::make_shared<transactions::TransactionQueue>();
		ref<transactions::TransactionQueue> AC_TRANSACTION_ARCHIVE = std::make_shared<transactions::TransactionQueue>();
		scene::Entity m_SelectedEntity;
	};
} // namespace assec::editor