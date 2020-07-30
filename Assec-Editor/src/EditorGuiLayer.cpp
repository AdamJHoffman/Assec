#include "EditorGuiLayer.h"

namespace assec::editor
{
	EditorGuiLayer::EditorGuiLayer(assec::Application& application, graphics::FrameBuffer* frameBuffer) : ImGuiLayer(application), m_FrameBuffer(frameBuffer) {}
	EditorGuiLayer::~EditorGuiLayer() {}
	void EditorGuiLayer::onEvent0(const events::Event& event)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([this](events::AppRenderEvent& event)
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

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						if (ImGui::MenuItem("Exit")) this->m_Application->close();
						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}


				bool show = true;
				ImGui::ShowDemoWindow(&show);

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
				ImGui::Begin("Viewport");

				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				this->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
				this->m_FrameBuffer->getFrameBufferProps().m_Width = static_cast<uint32_t>(viewportPanelSize.x);
				this->m_FrameBuffer->getFrameBufferProps().m_Height = static_cast<uint32_t>(viewportPanelSize.y);

				intptr_t textureID = static_cast<intptr_t>(this->m_FrameBuffer->m_ColorTetxure->m_RendererID);
				ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				ImGui::End();
				ImGui::PopStyleVar();

				ImGui::End();
				return false;
			});

	}
}