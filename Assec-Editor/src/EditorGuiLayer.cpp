#include "EditorGuiLayer.h"

#include <imgui.h>
#include <imnodes.h>
#include <implot.h>

#include "core/Input.h"
#include "core/Base.h"

#include "util/Loader.h"
#include "util/PlatformUtils.h"

#include "scene/SceneSerializer.h"

namespace assec::editor
{
	EditorGuiLayer::EditorGuiLayer(EditorApplication& application) : m_Application(&application) {}
	EditorGuiLayer::~EditorGuiLayer() {}
	void EditorGuiLayer::onAttach0()
	{
		imnodes::Initialize();
		ImPlot::CreateContext();
		this->setDarkThemecolors();
		this->m_SceneHierarchyPanel.setContext(*this->m_Application->m_ActiveScene);
		this->m_SceneHierarchyPanel.setSelectionCallback([&](const scene::Entity& entity)
			{
				this->m_InspectorPanel.setSelectedEntity(entity);
			});
		this->m_SceneHierarchyPanel.setTransactionCallback([&](ref<transactions::Transaction> transaction) 
			{
				this->m_Application->onTransaction(transaction);
			});
		this->m_InspectorPanel.setTransactionCallback([&](ref<transactions::Transaction> transaction)
			{
				this->m_Application->onTransaction(transaction);
			});
	}
	void EditorGuiLayer::onDetach0()
	{
		ImPlot::DestroyContext();
		imnodes::Shutdown();
	}
	void EditorGuiLayer::onEvent0(const events::Event& event)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([this](const events::AppRenderEvent& event)
			{
				TIME_FUNCTION;

				static bool dockspaceOpen = true;
				static bool opt_fullscreen_persistant = true;
				bool opt_fullscreen = opt_fullscreen_persistant;
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
				if (opt_fullscreen)
				{
					ImGuiViewport* viewport = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(viewport->Pos);
					ImGui::SetNextWindowSize(viewport->Size);
					ImGui::SetNextWindowViewport(viewport->ID);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
					window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}

				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("Assec Editor", &dockspaceOpen, window_flags);
				ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);

				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("AssecEditor");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				this->m_SceneHierarchyPanel.renderImGUI();
				this->m_InspectorPanel.renderImGUI();
				this->m_NodeEditor.renderImGUI();
				bool open = true;
				ImGui::ShowMetricsWindow(&open);
				ImPlot::ShowDemoWindow(&open);

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						if (ImGui::MenuItem("Exit")) this->m_Application->close();
						if (ImGui::MenuItem("New", "Ctrl+N"))
							this->newScene();
						if (ImGui::MenuItem("Open..", "Ctrl+O"))
							this->loadScene();
						if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
							this->saveScene();
						ImGui::EndMenu();
					}
					if (ImGui::Button("Run"))
					{
						AC_CLIENT_TRACE(">");
					}

					ImGui::EndMenuBar();
				}

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
				ImGui::Begin("Viewport");

				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				this->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
				this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Width = static_cast<uint32_t>(viewportPanelSize.x);
				this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Height = static_cast<uint32_t>(viewportPanelSize.y);

				ImGui::Image((void*)static_cast<intptr_t>(this->m_Application->m_FrameBuffer->getTextureAttachment(Type::COLOR_ATTACHMENT0).getNativeTexture()), ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				ImGui::End();
				ImGui::PopStyleVar();

				ImGui::End();
				return false;
			});
		dispatcher.dispatch<events::KeyPressedEvent>([&](const events::KeyPressedEvent& event)
			{
				bool control = Input::isKeyDown(KEY::KEY_LEFT_CONTROL) || Input::isKeyDown(KEY::KEY_RIGHT_CONTROL);
				bool shift = Input::isKeyDown(KEY::KEY_LEFT_SHIFT) || Input::isKeyDown(KEY::KEY_RIGHT_SHIFT);
				switch (event.m_Keycode)
				{
				case KEY::KEY_N:
				{
					if (control)
						this->newScene();
					return true;
					break;
				}
				case KEY::KEY_O:
				{
					if (control)
						this->loadScene();
					return true;
					break;
				}
				case KEY::KEY_S:
				{
					if (control && shift)
						this->saveSceneAs();
					else if (control && !shift)
						this->saveScene();
					return true;
					break;
				}
				case KEY::KEY_Y:
				{
					if (control && !this->m_Application->AC_TRANSACTION_ARCHIVE->getTransactionqueue().empty())
					{
						auto& lastTransaction = this->m_Application->AC_TRANSACTION_ARCHIVE->getTransactionqueue().back()->generateInverse();
						this->m_Application->AC_TRANSACTION_QUEUE->submit(lastTransaction);
						this->m_Application->AC_TRANSACTION_REDO_ARCHIVE->submit(lastTransaction);
						this->m_Application->AC_TRANSACTION_ARCHIVE->getTransactionqueue().pop_back();
					}
					return true;
					break;
				}
				case KEY::KEY_Z:
				{
					if (control && !this->m_Application->AC_TRANSACTION_REDO_ARCHIVE->getTransactionqueue().empty())
					{
						auto& lastTransaction = this->m_Application->AC_TRANSACTION_REDO_ARCHIVE->getTransactionqueue().back()->generateInverse();
						this->m_Application->AC_TRANSACTION_QUEUE->submit(lastTransaction);
						this->m_Application->AC_TRANSACTION_REDO_ARCHIVE->getTransactionqueue().pop_back();
					}
					return true;
					break;
				}
				}
				return false;
			});

	}
	void EditorGuiLayer::newScene()
	{
		this->m_Application->m_ActiveScene = std::make_shared<scene::Scene>();
		this->m_SceneHierarchyPanel.setContext(*this->m_Application->m_ActiveScene);
	}
	void EditorGuiLayer::loadScene()
	{
		util::FileDialogs::OpenFile({ "Assec Scene (*.assec)\0*.assec\0", [&](const char* filepath)
			{
			if (strlen(filepath) != 0)
				{
					this->newScene();
					scene::SceneSerializer serializer = scene::SceneSerializer(this->m_Application->m_ActiveScene);
					serializer.deserialize(filepath);
				}
			}
			});

	}
	void EditorGuiLayer::saveScene()
	{
		
		if (!this->m_Application->m_ActiveScene->getSaveFilePath().empty())
		{
				scene::SceneSerializer serializer(this->m_Application->m_ActiveScene);
				serializer.serialize(this->m_Application->m_ActiveScene->getSaveFilePath());
				if (graphics::WindowManager::getMainWindow().getWindowData().m_Title.back() == '*')
				{
					graphics::WindowManager::getMainWindow().getWindowData().m_Title.pop_back();
					graphics::WindowManager::getMainWindow().setTitle(graphics::WindowManager::getMainWindow().getWindowData().m_Title.c_str());
				}
		}
	}
	void EditorGuiLayer::saveSceneAs()
	{
		util::FileDialogs::SaveFile({ "Assec Scene (*.assec)\0*.assec\0", [&](const char* filepath)
			{
				if (strlen(filepath) != 0)
				{
						scene::SceneSerializer serializer(this->m_Application->m_ActiveScene);
						serializer.serialize(filepath);
						if (graphics::WindowManager::getMainWindow().getWindowData().m_Title.back() == '*')
						{
							graphics::WindowManager::getMainWindow().getWindowData().m_Title.pop_back();
							graphics::WindowManager::getMainWindow().setTitle(graphics::WindowManager::getMainWindow().getWindowData().m_Title.c_str());
						}
				}
			}
		});
	}
}
