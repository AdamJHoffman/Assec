#include <imgui.h>

#include "ViewportPanel.h"

namespace assec::editor
{
	ViewportPanel::ViewportPanel(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
		REF(EditorApplication) application) : EditorContext(callback, application, "Viewport") {}
	void ViewportPanel::render()
	{
		//m_ViewportFocused = ImGui::IsWindowFocused();
		//m_ViewportHovered = ImGui::IsWindowHovered();
		//this->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);


		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Width = static_cast<uint32_t>(viewportPanelSize.x);
		this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Height = static_cast<uint32_t>(viewportPanelSize.y);
		ImGui::Image((void*)static_cast<intptr_t>(this->m_Application->m_FrameBuffer->getTextureAttachment(Type::COLOR_ATTACHMENT0).getNativeTexture()), ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		
		this->gizmo.render();
	}
}