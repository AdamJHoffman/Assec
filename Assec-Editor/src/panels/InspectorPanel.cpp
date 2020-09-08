#include "InspectorPanel.h"
#include "scene/Components.h"
#include "util/Loader.h"
#include <windows.h>
#include <string.h>

namespace assec::editor
{
	InspectorPanel::~InspectorPanel() {}
	void InspectorPanel::setSelectedEntity(const scene::Entity& entity)
	{
		this->m_SelectedEntity = entity;
	}
	void InspectorPanel::renderImGUI()
	{
		ImGui::Begin("Inspector");
		if (this->m_SelectedEntity.operator bool())
		{
			if (this->m_SelectedEntity.hasComponent<scene::TagComponent>())
			{
				ImGui::BeginChild("Tag Component", ImVec2(ImGui::GetContentRegionAvailWidth(), 29), true);
				ImGui::Text(this->m_SelectedEntity.getComponent<scene::TagComponent>().m_Tag);
				ImGui::EndChild();
			}
			if (this->m_SelectedEntity.hasComponent<scene::MaterialComponent>())
			{
				ImGui::BeginChild("Material", ImVec2(ImGui::GetContentRegionAvailWidth(), 117), true);
				ImGui::Image((void*)static_cast<intptr_t>(this->m_SelectedEntity.getComponent<scene::MaterialComponent>().m_Material->m_Texture.m_RendererID), ImVec2(100, 100));
				ImGui::SameLine();
				if (ImGui::Button("Load Different Texture", ImGui::GetContentRegionAvail()))
				{
					OPENFILENAMEA ofn;
					char szFile[260];
					HWND hwnd = HWND();

					ZeroMemory(&ofn, sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = hwnd;
					ofn.lpstrFile = szFile;
					ofn.lpstrFile[0] = '\0';
					ofn.nMaxFile = sizeof(szFile);
					ofn.lpstrFilter = "All\0*.*\0Image\0*.jpg\0";
					ofn.nFilterIndex = 1;
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrInitialDir = NULL;
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


					if (GetOpenFileNameA(&ofn) == TRUE)
					{
						std::string path(ofn.lpstrFile);
						std::replace(path.begin(), path.end(), '\\', '/');
						assec::util::Loader::TextureData data = assec::util::Loader::loadImage(path.c_str());
						assec::graphics::Texture::TextureProps props = { data.m_Width, data.m_Height, assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true, Type::RGB, Type::RGB, Type::UNSIGNED_BYTE };
						this->m_SelectedEntity.getComponent<scene::MaterialComponent>().m_Material->m_Texture = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(data.m_Data, props);
					}
				}
				ImGui::EndChild();
			}
		}
		ImGui::End();
	}
}
