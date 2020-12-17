#include "EditorGuiLayer.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <imnodes.h>
#include <implot.h>

#include "input/Input.h"
#include "core/Base.h"

#include "util/Loader.h"
#include "util/PlatformUtils.h"
#include "util/Dispatcher.h"

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
		this->m_OpenContexts.push_back(makeRef<InspectorPanel>([&](ref<transactions::Transaction> transaction)
			{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
		this->m_OpenContexts.push_back(makeRef<SceneHierarchyPanel>([&](ref<transactions::Transaction> transaction)
			{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
		this->m_OpenContexts.push_back(makeRef<NodeEditor>([&](ref<transactions::Transaction> transaction)
			{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
		this->m_OpenContexts.push_back(makeRef<ViewportPanel>([&](ref<transactions::Transaction> transaction)
			{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
	}
	void EditorGuiLayer::onDetach0()
	{
		ImPlot::DestroyContext();
		imnodes::Shutdown();
	}
	void EditorGuiLayer::onEvent0(const events::Event& event)
	{
		util::EventDispatcher dispatcher = util::EventDispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([this](const events::AppRenderEvent& event)
			{
				ImGuizmo::BeginFrame();
				TIME_FUNCTION;
				this->m_OpenContexts.erase(std::remove_if(this->m_OpenContexts.begin(), this->m_OpenContexts.end(),
					[](CONST_REF(ref<EditorContext>) context) 
					{
						return !context->isVisible();
					}), this->m_OpenContexts.end());

				// ----------Dockspace setup----------

				bool dockspaceOpen = true;
				bool opt_fullscreen_persistant = true;
				bool opt_fullscreen = opt_fullscreen_persistant;
				ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

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

				// ----------Dockspace setup----------

				for (auto& context : this->m_OpenContexts)
				{
					context->renderImGUI();
				}
				bool open = true;
				//ImGui::ShowDemoWindow(&open);
				ImGui::ShowMetricsWindow(&open);
				//ImPlot::ShowDemoWindow(&open);

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
					if (ImGui::BeginMenu("View"))
					{
						if (ImGui::BeginMenu("Show window"))
						{
							if (ImGui::MenuItem("Inspector", 0, false, std::find_if(this->m_OpenContexts.begin(),
								this->m_OpenContexts.end(), [](CONST_REF(ref<EditorContext>) context)
								{ return context->getName() == "Inspector"; }) == this->m_OpenContexts.end()))
							{
								this->m_OpenContexts.push_back(makeRef<InspectorPanel>([&](ref<transactions::Transaction> transaction)
									{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
							}
							if (ImGui::MenuItem("Scene Hierarchy", 0, false, std::find_if(this->m_OpenContexts.begin(),
								this->m_OpenContexts.end(), [](CONST_REF(ref<EditorContext>) context)
								{ return context->getName() == "Scene Hierarchy"; }) == this->m_OpenContexts.end()))
							{
								this->m_OpenContexts.push_back(makeRef<SceneHierarchyPanel>(
									[&](ref<transactions::Transaction> transaction)
									{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
							}
							if (ImGui::MenuItem("Node Editor", 0, false, std::find_if(this->m_OpenContexts.begin(),
								this->m_OpenContexts.end(), [](CONST_REF(ref<EditorContext>) context)
								{ return context->getName() == "Node Editor"; }) == this->m_OpenContexts.end()))
							{
								this->m_OpenContexts.push_back(makeRef<NodeEditor>(
									[&](ref<transactions::Transaction> transaction)
									{ this->m_Application->onTransaction(transaction); }, *this->m_Application));
							}
							if (ImGui::MenuItem("Viewport", 0, false, std::find_if(this->m_OpenContexts.begin(),
								this->m_OpenContexts.end(), [](CONST_REF(ref<EditorContext>) context)
								{ return context->getName() == "Viewport"; }) == this->m_OpenContexts.end()))
							{
								this->m_OpenContexts.push_back(makeRef<ViewportPanel>(
									[&](ref<transactions::Transaction> transaction)
									{ this->m_Application->onTransaction(transaction);}, *this->m_Application));
							}
							ImGui::EndMenu();
						}
						ImGui::EndMenu();
					}
					if (ImGui::Button(this->m_Application->m_CurrentState == ApplicationState::EDITOR ? "RUN" : "STOP"))
					{
						if (this->m_Application->m_CurrentState == ApplicationState::EDITOR)
						{
							this->m_Application->getActiveScene().reg().view<scene::NativeScriptComponent>().each([&](auto entity, auto& nsc)
								{
									if (!nsc.m_Instance)
									{
										nsc.m_Instance = nsc.InstantiateScript(entity, &this->m_Application->getActiveScene());
									}
								});
							this->m_Application->getActiveScene().reg().view<scene::CameraComponent>().each([&](auto entityID, auto& udc)
								{
									if (udc.m_Primary)
									{
										this->m_Application->getActiveScene().setActiveCamera(udc.m_Camera.m_Projection);
									}
								});
							this->m_Application->m_CurrentState = ApplicationState::GAME;
						}
						else if (this->m_Application->m_CurrentState == ApplicationState::GAME)
						{
							this->m_Application->getActiveScene().reg().view<scene::NativeScriptComponent>().each([&](auto entity, auto& nsc)
								{
									
									nsc.m_Instance = nullptr;
									
								});
							this->m_Application->m_CurrentState = ApplicationState::EDITOR;
						}
					}

					ImGui::EndMenuBar();
				}

				ImGui::End();
				return false;
			});
		dispatcher.dispatch<events::KeyPressedEvent>([&](const events::KeyPressedEvent& event)
			{
				bool control = input::Input::isKeyDown(KEY::KEY_LEFT_CONTROL) || input::Input::isKeyDown(KEY::KEY_RIGHT_CONTROL);
				bool shift = input::Input::isKeyDown(KEY::KEY_LEFT_SHIFT) || input::Input::isKeyDown(KEY::KEY_RIGHT_SHIFT);
				switch (event.getKeycode())
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
		this->m_Application->setActiveScene(std::make_shared<scene::Scene>());
	}
	void EditorGuiLayer::loadScene()
	{
		util::FileDialogs::OpenFile({ "Assec Scene (*.assec)\0*.assec\0", [&](const char* filepath)
			{
			if (strlen(filepath) != 0)
				{
					this->newScene();
					scene::SceneSerializer serializer = scene::SceneSerializer(this->m_Application->getRawActiveScene());
					serializer.deserialize(filepath);
				}
			}
			});

	}
	void EditorGuiLayer::saveScene()
	{
		
		if (!this->m_Application->getActiveScene().getSaveFilePath().empty())
		{
				scene::SceneSerializer serializer(this->m_Application->getRawActiveScene());
				serializer.serialize(this->m_Application->getActiveScene().getSaveFilePath());
				if (graphics::WindowManager::getMainWindow().getWindowData().title.back() == '*')
				{
					graphics::WindowManager::getMainWindow().getWindowData().title.pop_back();
					graphics::WindowManager::getMainWindow().setTitle(graphics::WindowManager::getMainWindow().getWindowData().title.c_str());
				}
		}
	}
	void EditorGuiLayer::saveSceneAs()
	{
		util::FileDialogs::SaveFile({ "Assec Scene (*.assec)\0*.assec\0", [&](const char* filepath)
			{
				if (strlen(filepath) != 0)
				{
						scene::SceneSerializer serializer(this->m_Application->getRawActiveScene());
						serializer.serialize(filepath);
						if (graphics::WindowManager::getMainWindow().getWindowData().title.back() == '*')
						{
							graphics::WindowManager::getMainWindow().getWindowData().title.pop_back();
							graphics::WindowManager::getMainWindow().setTitle(graphics::WindowManager::getMainWindow().getWindowData().title.c_str());
						}
				}
			}
		});
	}
}
