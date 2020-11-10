
#include "InspectorPanel.h"

#include <windows.h>
#include <string.h>

#include <imgui.h>
#include <imgui_internal.h>

#include "scene/Components.h"

#include "util/Loader.h"
#include "util/PlatformUtils.h"

namespace assec::editor
{
	InspectorPanel::~InspectorPanel() {}
	void InspectorPanel::setSelectedEntity(const scene::Entity& entity)
	{
		this->m_SelectedEntity = entity;
	}
	void InspectorPanel::setTransactionCallback(const std::function<void(ref<transactions::Transaction>)>& transactionCallback)
	{
		this->m_TransactionCallback = transactionCallback;
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
	void InspectorPanel::drawComponent(const char* name, scene::Entity entity, UIFunction uiFunction)
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

			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					this->m_TransactionCallback(std::make_shared<transactions::ComponentRemovalTransaction<T>>(entity));

				ImGui::EndPopup();
			}
			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}
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
			drawComponent<scene::TransformComponent>("Transform Component", this->m_SelectedEntity, [&](auto& component)
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
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.translation[i], 0.0f));
								ImGui::PopFont();
								ImGui::PopStyleColor(3);

								ImGui::SameLine();
								float value = component.translation[i];
								if(ImGui::DragFloat(&ids[i][0], &value, 0.1f, 0.0f, 0.0f, "%.2f"))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.translation[i], value));
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
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.rotation[i], 0.0f));
								ImGui::PopFont();
								ImGui::PopStyleColor(3);

								ImGui::SameLine();
								float value = component.rotation[i];
								if (ImGui::DragFloat(&ids[i][0], &value, 0.1f, 0.0f, 0.0f, "%.2f"))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.rotation[i], value));
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
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.scale[i], 1.0f));
								ImGui::PopFont();
								ImGui::PopStyleColor(3);

								ImGui::SameLine();
								float value = component.scale[i];
								if (ImGui::DragFloat(&ids[i][0], &value, 0.1f, 0.0f, 0.0f, "%.2f"))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.scale[i], value));
								ImGui::PopItemWidth();
								if (i < numOfElements - 1)
								{
									ImGui::SameLine();
								}
							}

						});
				});
			drawComponent<scene::NativeScriptComponent>("Native Script Component", this->m_SelectedEntity, [&](auto& component)
				{
					auto& keys = util::Keys(component.m_Instance->getFields());
					for (auto& key : keys)
					{
						auto& value = component.m_Instance->getFields().at(key);
						if (value->getAccess() == util::Access::PUBLIC)
						{
							util::FieldDispatcher dispatcher = util::FieldDispatcher(*value);
							dispatcher.dispatch<float>([&](float& value)
								{
									drawUIColumned(key.c_str(), 1, [&](auto& numOfElements)
										{
											float temp = value;
											if(ImGui::DragFloat((std::string("##") + key).c_str(), &temp))
												this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&value, temp));
										});
								});
							dispatcher.dispatch<bool>([&](bool& value)
								{
									drawUIColumned(key.c_str(), 1, [&](auto& numOfElements)
										{
											bool temp = value;
											if (ImGui::Checkbox((std::string("##") + key).c_str(), &temp))
												this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<bool>>(&value, temp));
										});
								});
							dispatcher.dispatch<int>([&](int& value)
								{
									drawUIColumned(key.c_str(), 1, [&](auto& numOfElements)
										{
											int temp = value;
											if (ImGui::DragInt((std::string("##") + key).c_str(), &temp))
												this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<int>>(&value, temp));
										});
								});
							dispatcher.dispatch<std::string>([&](std::string &value)
								{
									drawUIColumned(key.c_str(), 1, [&](auto& numOfElements)
										{
											char* temp = const_cast<char*>(value.c_str());
											if (ImGui::InputText((std::string("##") + key).c_str() , temp, sizeof(temp)))
												this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<std::string>>(&value, std::string(temp)));
										});
								});
						}
					}

				});
			drawComponent<scene::MeshComponent>("Mesh Component", this->m_SelectedEntity, [&](auto& component)
				{
					drawUIColumned("path", 1, [&](auto& numOfElements)
						{
							if (ImGui::Button(component.m_Path.c_str(), ImVec2{ ImGui::GetContentRegionAvail().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f }))
							{
								util::FileDialogs::OpenFile({ "gltf\0*.gltf\0glb\0*.glb\0", [&](const char* filepath)
									   {
										   this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<std::string>>(&component.m_Path, filepath, [&](std::string& path) 
											   {
													auto& mesh = util::Loader::loadgltfMesh(path.c_str());
													this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<graphics::Mesh>>(&*component.m_Mesh, mesh[0]));
											   }));
									   }
									});
							}
						});
				});
			drawComponent<scene::MaterialComponent>("Material Component", this->m_SelectedEntity, [&](auto& component)
				{
					drawUIColumned("texture", 1, [&](auto& numOfElements)
						{
							if (ImGui::Button(component.m_TexturePath.c_str(), ImVec2{ ImGui::GetContentRegionAvail().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f }))
							{
								util::FileDialogs::OpenFile({ "jpg\0*.jpg\0png\0*.png*\0", [&](const char* filepath)
									   {
										   this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<std::string>>(&component.m_TexturePath, std::string(filepath), [&](std::string& path) 
											   {
													std::replace(path.begin(), path.end(), '\\', '/');
													assec::graphics::Texture::TextureProps props = { assec::Type::CLAMP_TO_EDGE, Type::RGB8, Type::RGB, Type::UNSIGNED_BYTE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true };
													this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<ref<graphics::Texture>>>(&component.m_Material->m_Texture, graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(path, props)));
											   }));
									   }
									});
							}
						});
					drawUIColumned("shader", 1, [&](auto& numOfElements)
						{
							if (ImGui::Button(component.m_ShaderPath.c_str(), ImVec2{ ImGui::GetContentRegionAvail().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f }))
							{
								util::FileDialogs::OpenFile({ "shader\0*.shader\0", [&](const char* filepath)
									   {
										   this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<std::string>>(&component.m_ShaderPath, std::string(filepath),[&](std::string& path)
											   {
												   std::replace(path.begin(), path.end(), '\\', '/');
												   this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<ref<graphics::ShaderProgram>>>(&component.m_Material->m_ShaderProgram, graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createShaderProgram(util::Loader::loadFile(component.m_ShaderPath.c_str()))));
												}));
										}
									});
							}
						});
				});
			drawComponent<scene::CameraComponent>("Camera Component", this->m_SelectedEntity, [&](auto& component)
				{
					drawUIColumned("Primary", 1, [&](auto& numOfElements)
						{
							bool value = component.m_Primary;
							if(ImGui::Checkbox("##PrimaryBox", &value))
								this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<bool>>(&component.m_Primary, value));
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
										this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<scene::Camera::projectionType>>(&component.m_Type, static_cast<scene::Camera::projectionType>(i)));
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
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.m_PerspectiveFov, glm::radians(perspectiveVerticalFov)));
							});
						drawUIColumned("Near", 1, [&](auto& numOfElements)
							{
								float perspectiveNear = component.m_PerspectiveNear;
								if (ImGui::DragFloat("##NearFloat", &perspectiveNear))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.m_PerspectiveNear, perspectiveNear));
							});
						drawUIColumned("Far", 1, [&](auto& numOfElements)
							{
								float perspectiveFar = component.m_PerspectiveFar;
								if (ImGui::DragFloat("##FarFloat", &perspectiveFar))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.m_PerspectiveFar, perspectiveFar));
							});
					}
					if (component.m_Type == scene::Camera::projectionType::ORTHOGRAPHIC)
					{
						drawUIColumned("Size", 1, [&](auto& numOfElements)
							{
								float orthoSize = component.m_OrthographicSize;
								if (ImGui::DragFloat("##SizeFloat", &orthoSize))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.m_OrthographicSize, orthoSize));
							});
						drawUIColumned("Near", 1, [&](auto& numOfElements)
							{
								float orthoNear = component.m_OrthographicNear;
								if (ImGui::DragFloat("##NearFloat", &orthoNear))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.m_OrthographicNear, orthoNear));
							});
						drawUIColumned("Far", 1, [&](auto& numOfElements)
							{
								float orthoFar = component.m_OrthographicFar;
								if (ImGui::DragFloat("##FarFloat", &orthoFar))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<float>>(&component.m_OrthographicFar, orthoFar));
							});
						drawUIColumned("Fixed Aspect Ratio", 1, [&](auto& numOfElements)
							{
								bool value = component.m_FixedAspectRatio;
								if(ImGui::Checkbox("##Fixed Aspect Ratio box", &value))
									this->m_TransactionCallback(std::make_shared<transactions::ValueChangedTransaction<bool>>(&component.m_FixedAspectRatio, value));
							});
					}
				});
			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");

			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Mesh"))
				{
					if (!this->m_SelectedEntity.hasComponent<scene::MeshComponent>())
					{
						this->m_TransactionCallback(std::make_shared<transactions::ComponentCreationTransaction<scene::MeshComponent>>(this->m_SelectedEntity));
					}
					else
					{
						AC_CORE_WARNING("Entity {0} already has component of type {0}!", static_cast<uint32_t>(this->m_SelectedEntity), typeid(scene::MeshComponent).name());
					}
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Material"))
				{
					if (!this->m_SelectedEntity.hasComponent<scene::MaterialComponent>())
					{
						this->m_TransactionCallback(std::make_shared<transactions::ComponentCreationTransaction<scene::MaterialComponent>>(this->m_SelectedEntity));
					}
					else
					{
						AC_CORE_WARNING("Entity {0} already has component of type {0}!", static_cast<uint32_t>(this->m_SelectedEntity), typeid(scene::MaterialComponent).name());
					}
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Camera"))
				{
					if (!this->m_SelectedEntity.hasComponent<scene::CameraComponent>())
					{
						this->m_TransactionCallback(std::make_shared<transactions::ComponentCreationTransaction<scene::CameraComponent>>(this->m_SelectedEntity));
					}
					else
					{
						AC_CORE_WARNING("Entity {0} already has component of type {0}!", static_cast<uint32_t>(this->m_SelectedEntity), typeid(scene::CameraComponent).name());
					}
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Native Script Component"))
				{
					if (!this->m_SelectedEntity.hasComponent<scene::NativeScriptComponent>())
					{
						this->m_TransactionCallback(std::make_shared<transactions::ComponentCreationTransaction<scene::NativeScriptComponent>>(this->m_SelectedEntity));
					}
					else
					{
						AC_CORE_WARNING("Entity {0} already has component of type {0}!", static_cast<uint32_t>(this->m_SelectedEntity), typeid(scene::NativeScriptComponent).name());
					}
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}
