#include "acpch.h"
#include "ImguiLayer.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace assec
{
	ImGuiLayer::ImGuiLayer(const assec::Application& application) : m_Application(&application) {}
	ImGuiLayer::~ImGuiLayer() {}
	void ImGuiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.BackendPlatformName = "imgui_impl_opengl3";

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)this->m_Application->AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_NativeWindow, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::end(const float& deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(this->m_Application->AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_Width,
			this->m_Application->AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_Height);
		io.DeltaTime = deltaTime;

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ref<assec::graphics::Window> backupCurrentContext = this->m_Application->AC_WINDOW_MANAGER->getWindows()[0];
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			backupCurrentContext->makeCurrent();
		}
	}
} // namespace assec::editor