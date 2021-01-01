#pragma once

#include <imgui.h>

#include "../transactions/Transaction.h"

#include "../EditorApplication.h"

namespace assec::editor
{
	class EditorContext
	{
	public:
		EditorContext(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
			std::function<void(CONST_REF(bool))> blockCallback,
			REF(EditorApplication) application,
			CONST_REF(std::string) name = "Context") : m_TransactionCallback(callback),
			m_BlockEventsCallback(blockCallback),
			m_Name(name), 
			m_Application(&application){}
		virtual ~EditorContext() = default;
		INLINE void renderImGUI() { this->begin(); this->render(); this->end(); }
		INLINE void show() { this->m_Open = true; }
		INLINE CONST_REF(bool) isVisible() const { return this->m_Open; }
		INLINE CONST_REF(std::string) getName() const { return this->m_Name; }
	protected:
		virtual void begin0() {}
		virtual void end0() {}
		virtual void render() = 0;

		bool m_Open = true;
		std::function<void(ref<transactions::Transaction>)> m_TransactionCallback;
		std::function<void(CONST_REF(bool))> m_BlockEventsCallback;
		std::string m_Name = "Context";
		EditorApplication* m_Application = nullptr;
	private:
		INLINE void begin() { ImGui::Begin(this->m_Name.c_str(), &this->m_Open); this->begin0(); }
		INLINE void end() { this->end0(); ImGui::End(); }
	};
}