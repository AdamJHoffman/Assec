#include "acpch.h"
#include "ImguiLayer.h"
#include "event/EngineEvents.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"
#include "event/WindowEvents.h"

#include <imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace assec
{
	ImGuiLayer::ImGuiLayer(assec::Application& application) : m_Application(&application) {}
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
	void ImGuiLayer::onEvent(const events::Event& event)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([this](events::AppRenderEvent& event)
			{
				this->begin();
				this->onEvent0(event);
				this->end(event.m_Delta);
				return false;
			});
		dispatcher.dispatch<events::AppUpdateEvent>([this](events::AppUpdateEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::PathDroppedEvent>([this](events::PathDroppedEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::KeyPressedEvent>([this](events::KeyPressedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::KeyRepeatedEvent>([this](events::KeyRepeatedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::KeyReleasedEvent>([this](events::KeyReleasedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::CharTypedEvent>([this](events::CharTypedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseMovedEvent>([this](events::MouseMovedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseButtonPressedEvent>([this](events::MouseButtonPressedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseButtonReleasedEvent>([this](events::MouseButtonReleasedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseScrolledEvent>([this](events::MouseScrolledEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::CursorEnteredEvent>([this](events::CursorEnteredEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::CursorExitedEvent>([this](events::CursorExitedEvent& event)
			{
				this->onEvent0(event);
				return false;
			});

		dispatcher.dispatch<events::WindowCloseEvent>([this](events::WindowCloseEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowFocusEvent>([this](events::WindowFocusEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowFocusLostEvent>([this](events::WindowFocusLostEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowResizeEvent>([this](events::WindowResizeEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowContentScaleEvent>([this](events::WindowContentScaleEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowMoveEvent>([this](events::WindowMoveEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowMinimizeEvent>([this](events::WindowMinimizeEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowMaximizeEvent>([this](events::WindowMaximizeEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowRestoreEvent>([this](events::WindowRestoreEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowRefreshEvent>([this](events::WindowRefreshEvent& event)
			{
				this->onEvent0(event);
				return false;
			});

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
		io.DisplaySize = ImVec2(static_cast<float>(this->m_Application->AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_Width),
			static_cast<float>(this->m_Application->AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_Height));
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
