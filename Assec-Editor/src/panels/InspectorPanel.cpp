#include "InspectorPanel.h"
#include "scene/Components.h"
#include "util/Loader.h"
#include <windows.h>
#include <string.h>

#include <imgui_internal.h>

namespace assec::editor
{
	InspectorPanel::~InspectorPanel() {}
	void InspectorPanel::setSelectedEntity(const scene::Entity& entity)
	{
		this->m_SelectedEntity = entity;
	}
	template<typename UIFunction>
	void drawUIColumned(const char* label, int numOfElements, UIFunction uiFunction, float columnWidth = 150.0f)
	{
		ImGui::PushID(label);

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(numOfElements, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		uiFunction(numOfElements);

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}
	template<typename T, typename UIFunction>
	void drawComponent(const char* name, scene::Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.hasComponent<T>())
		{
			auto& component = entity.getComponent<T>();

			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name);
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}
			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}
			if (removeComponent)
				entity.removeComponent<T>();
		}
	}
	void InspectorPanel::renderImGUI()
	{
		ImGui::Begin("Inspector");
		if (this->m_SelectedEntity)
		{
			drawComponent<scene::TagComponent>("Tag Component", this->m_SelectedEntity, [&](auto& component)
				{
					drawUIColumned("tag", 1, [&](auto& numOfElements)
						{
							char buffer[256];
							memset(buffer, 0, sizeof(buffer));
							strcpy_s(buffer, sizeof(buffer), component.m_Tag.c_str());
							if (ImGui::InputText("##tag", buffer, sizeof(buffer)))
							{
								component.m_Tag = std::string(buffer);
							}
						});
				});
			drawComponent<scene::TransformComponent>("Transform Component", this->m_SelectedEntity, [](auto& component)
				{
					const char names[3][2] = { {"X"}, {"Y"}, {"Z"} };
					const char ids[3][4] = { {"##X"}, {"##Y"}, {"##Z"} };
					ImVec4 colors[3][3] = {
						{ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }},
						{ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }},
						{ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f }, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f }, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f }} };
					drawUIColumned("translation", component.translation.length(), [&](auto& numOfElements)
						{
							ImGuiIO& io = ImGui::GetIO();
							auto boldFont = io.Fonts->Fonts[0];

							float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
							ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

							for (int i = 0; i < numOfElements; ++i)
							{
								ImGui::PushStyleColor(ImGuiCol_Button, colors[i][0]);
								ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[i][1]);
								ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[i][2]);
								ImGui::PushFont(boldFont);
								if (ImGui::Button(&names[i][0], buttonSize))
									component.translation[i] = 0;
								ImGui::PopFont();
								ImGui::PopStyleColor(3);

								ImGui::SameLine();
								ImGui::DragFloat(&ids[i][0], &component.translation[i], 0.1f, 0.0f, 0.0f, "%.2f");
								ImGui::PopItemWidth();
								if (i < numOfElements - 1)
								{
									ImGui::SameLine();
								}
							}

						});

					drawUIColumned("rotation", component.rotation.length(), [&](auto& numOfElements)
						{
							ImGuiIO& io = ImGui::GetIO();
							auto boldFont = io.Fonts->Fonts[0];

							float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
							ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

							for (int i = 0; i < numOfElements; ++i)
							{
								ImGui::PushStyleColor(ImGuiCol_Button, colors[i][0]);
								ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[i][1]);
								ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[i][2]);
								ImGui::PushFont(boldFont);
								if (ImGui::Button(&names[i][0], buttonSize))
									component.rotation[i] = 0;
								ImGui::PopFont();
								ImGui::PopStyleColor(3);

								ImGui::SameLine();
								ImGui::DragFloat(&ids[i][0], &component.rotation[i], 0.1f, 0.0f, 0.0f, "%.2f");
								ImGui::PopItemWidth();
								if (i < numOfElements - 1)
								{
									ImGui::SameLine();
								}
							}

						});

					drawUIColumned("scale", component.scale.length(), [&](auto& numOfElements)
						{
							ImGuiIO& io = ImGui::GetIO();
							auto boldFont = io.Fonts->Fonts[0];

							float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
							ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

							for (int i = 0; i < numOfElements; ++i)
							{
								ImGui::PushStyleColor(ImGuiCol_Button, colors[i][0]);
								ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[i][1]);
								ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[i][2]);
								ImGui::PushFont(boldFont);
								if (ImGui::Button(&names[i][0], buttonSize))
									component.scale[i] = 1;
								ImGui::PopFont();
								ImGui::PopStyleColor(3);

								ImGui::SameLine();
								ImGui::DragFloat(&ids[i][0], &component.scale[i], 0.1f, 0.0f, 0.0f, "%.2f");
								ImGui::PopItemWidth();
								if (i < numOfElements - 1)
								{
									ImGui::SameLine();
								}
							}

						});
				});
			drawComponent<scene::MeshComponent>("Mesh Component", this->m_SelectedEntity, [](auto& component)
				{
					drawUIColumned("path", 1, [&](auto& numOfElements)
						{
							if (ImGui::Button(component.m_Path.c_str(), ImVec2{ ImGui::GetContentRegionAvail().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f }))
							{
								util::Loader::queueOpenFileDialogRequest(util::Loader::FileDialogData{ "gltf\0*.gltf\0glb\0*.glb\0All\0*.*\0", [&](const char* filepath)
								{
									auto& mesh = util::Loader::loadgltfMesh(filepath);
									component.m_Path = std::string(filepath);
									*component.m_Mesh = mesh[0];
								} });
							}
						});
				});
			drawComponent<scene::MaterialComponent>("Material Component", this->m_SelectedEntity, [](auto& component)
				{
					drawUIColumned("texture", 1, [&](auto& numOfElements)
						{
							if (ImGui::Button(component.m_TexturePath.c_str(), ImVec2{ ImGui::GetContentRegionAvail().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f }))
							{
								util::Loader::queueOpenFileDialogRequest(util::Loader::FileDialogData{ "jpg\0*.jpg\0png\0*.png\0All\0*.*\0", [&](const char* filepath)
								{
									std::string path(filepath);
									std::replace(path.begin(), path.end(), '\\', '/');
									component.m_TexturePath = path;
									assec::util::Loader::TextureData data = assec::util::Loader::loadImage(path.c_str());
									assec::graphics::Texture::TextureProps props = { data.m_Width, data.m_Height, assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, Type::RGB, Type::RGB, Type::UNSIGNED_BYTE, true, true };
									component.m_Material->m_Texture = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(data.m_Data, props);
								} });
							}
						});
					drawUIColumned("shader", 1, [&](auto& numOfElements)
						{
							if (ImGui::Button(component.m_ShaderPath.c_str(), ImVec2{ ImGui::GetContentRegionAvail().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f }))
							{
								util::Loader::queueOpenFileDialogRequest(util::Loader::FileDialogData{ "shader\0*.shader\0All\0*.*\0", [&](const char* filepath)
								{
									std::string path(filepath);
									std::replace(path.begin(), path.end(), '\\', '/');
									component.m_ShaderPath = path;
									component.m_Material->m_ShaderProgram = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createShaderProgram(util::Loader::loadFile(filepath));
								}
									});
							}
						});
				});
			drawComponent<scene::CameraComponent>("Camera Component", this->m_SelectedEntity, [&](auto& component)
				{
					drawUIColumned("Primary", 1, [&](auto& numOfElements)
						{
							ImGui::Checkbox("##PrimaryBox", &component.m_Primary);
						});

					drawUIColumned("Projection", 1, [&](auto& numOfElements)
						{
							const char* projectionTypeStrings[] = { "Orthographic", "Perspective" };
							const char* currentProjectionTypeString = projectionTypeStrings[static_cast<int>(component.m_Type)];
							if (ImGui::BeginCombo("##ProjectionCombo", currentProjectionTypeString))
							{
								for (int i = 0; i < 2; i++)
								{
									bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
									if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
									{
										currentProjectionTypeString = projectionTypeStrings[i];
										component.m_Type = static_cast<scene::Camera::projectionType>(i);
									}

									if (isSelected)
										ImGui::SetItemDefaultFocus();
								}

								ImGui::EndCombo();
							}
						});
					if (component.m_Type == scene::Camera::projectionType::PERSPECTIVE)
					{
						drawUIColumned("Fov", 1, [&](auto& numOfElements)
							{
								float perspectiveVerticalFov = glm::degrees(component.m_PerspectiveFov);
								if (ImGui::DragFloat("##FOVFloat", &perspectiveVerticalFov))
									component.m_PerspectiveFov = glm::radians(perspectiveVerticalFov);
							});
						drawUIColumned("Near", 1, [&](auto& numOfElements)
							{
								float perspectiveNear = component.m_PerspectiveNear;
								if (ImGui::DragFloat("##NearFloat", &perspectiveNear))
									component.m_PerspectiveNear = perspectiveNear;
							});
						drawUIColumned("Far", 1, [&](auto& numOfElements)
							{
								float perspectiveFar = component.m_PerspectiveFar;
								if (ImGui::DragFloat("##FarFloat", &perspectiveFar))
									component.m_PerspectiveFar = perspectiveFar;
							});
					}
					if (component.m_Type == scene::Camera::projectionType::ORTHOGRAPHIC)
					{
						drawUIColumned("Size", 1, [&](auto& numOfElements)
							{
								float orthoSize = component.m_OrthographicSize;
								if (ImGui::DragFloat("##SizeFloat", &orthoSize))
									component.m_OrthographicSize = orthoSize;
							});
						drawUIColumned("Near", 1, [&](auto& numOfElements)
							{
								float orthoNear = component.m_OrthographicNear;
								if (ImGui::DragFloat("##NearFloat", &orthoNear))
									component.m_OrthographicNear = orthoNear;
							});
						drawUIColumned("Far", 1, [&](auto& numOfElements)
							{
								float orthoFar = component.m_OrthographicFar;
								if (ImGui::DragFloat("##FarFloat", &orthoFar))
									component.m_OrthographicFar = orthoFar;
							});
						drawUIColumned("Fixed Aspect Ratio", 1, [&](auto& numOfElements)
							{
								ImGui::Checkbox("##Fixed Aspect Ratio box", &component.m_FixedAspectRatio);
							});
					}
				});
			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");

			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Mesh"))
				{
					this->m_SelectedEntity.addComponent<scene::MeshComponent>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Material"))
				{
					this->m_SelectedEntity.addComponent<scene::MaterialComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}
