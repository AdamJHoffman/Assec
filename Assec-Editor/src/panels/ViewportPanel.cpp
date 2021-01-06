#include <imgui.h>

#include "ViewportPanel.h"

namespace assec::editor
{
	ViewportPanel::ViewportPanel(CONST_REF(std::function<void(ref<transactions::Transaction>)>) callback,
		std::function<void(CONST_REF(bool))> blockCallback,
		REF(EditorApplication) application) : EditorContext(callback, blockCallback, application, "Viewport") {}
	void ViewportPanel::render()
	{
		bool m_ViewportFocused = ImGui::IsWindowFocused();
		bool m_ViewportHovered = ImGui::IsWindowHovered();
		this->m_BlockEventsCallback(!m_ViewportFocused && !m_ViewportHovered);

		glm::vec2 pos = { ImGui::GetWindowPos().x, ImGui::GetWindowPos().y};
		auto& cursorPos = graphics::WindowManager::getMainWindow().getCursorPos();
		glm::vec2 relativeCursorPos = cursorPos - pos;

		if (relativeCursorPos.x >= 0 && relativeCursorPos.x <= this->m_Application->m_FrameBuffer->getTextureAttachment(FrameBufferAttachment::COLOR_ATTACHMENT1).getWidth()
			&& relativeCursorPos.y >= 0 && relativeCursorPos.y <= this->m_Application->m_FrameBuffer->getTextureAttachment(FrameBufferAttachment::COLOR_ATTACHMENT1).getHeigth())
		{
			
			if (input::Input::isMouseButtonDown(MOUSE::MOUSE_BUTTON_LEFT))
			{
				this->m_Application->m_FrameBuffer->bind();
				graphics::WindowManager::getMainWindow().getWindowData().graphicsContext->readBuffer(DrawBuffer::COLOR_ATTACHMENT1);
				uint32_t id = *((uint32_t*)&graphics::WindowManager::getMainWindow().getWindowData().graphicsContext->readPixels(relativeCursorPos, { 1, 1 }, InternalFormat::R32UI).front());
				this->m_Application->m_FrameBuffer->unbind();
				if (id > 0)
				{
					this->m_Application->m_SelectedEntity = scene::Entity(entt::entity(id), &(*this->m_Application->getRawActiveScene()));
				}
				else
				{
					this->m_Application->m_SelectedEntity = scene::Entity();
				}
			}
		}

		//ImGuizmo::SetOrthographic(false);
		//ImGuizmo::SetDrawlist();
		//
		//float windowWidth = (float)ImGui::GetWindowWidth();
		//float windowHeight = (float)ImGui::GetWindowHeight();
		//ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
		//
		//glm::mat4 view = this->m_Application->m_Camera.getViewMatrix();
		//const glm::mat4& projection = this->m_Application->m_Camera.m_Projection;
		//ImGuizmo::DrawGrid(glm::value_ptr(view), glm::value_ptr(projection), glm::value_ptr(glm::mat4(1.0f)), 10.0f);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		this->m_Application->m_FrameBuffer->getFrameBufferProps().width = static_cast<uint32_t>(viewportPanelSize.x);
		this->m_Application->m_FrameBuffer->getFrameBufferProps().height = static_cast<uint32_t>(viewportPanelSize.y);
		ImGui::Image((void*)static_cast<intptr_t>(this->m_Application->m_FrameBuffer->getTextureAttachment(FrameBufferAttachment::COLOR_ATTACHMENT0).getNativeTexture()),
			ImVec2{ static_cast<float>(this->m_Application->m_FrameBuffer->getTextureAttachment(FrameBufferAttachment::COLOR_ATTACHMENT0).getWidth()),
			static_cast<float>(this->m_Application->m_FrameBuffer->getTextureAttachment(FrameBufferAttachment::COLOR_ATTACHMENT0).getHeigth()) }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		this->gizmo.render();
	}
}