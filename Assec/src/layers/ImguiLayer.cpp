#include "acpch.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <imgui.h>

#include "ImguiLayer.h"

#include "graphics/WindowManager.h"

#include "event/EngineEvents.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"
#include "event/WindowEvents.h"

namespace assec
{
	ImGuiLayer::ImGuiLayer() {}
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

		io.Fonts->AddFontFromFileTTF("res/fonts/open_sans/OpenSans-Bold.ttf", 18);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/open_sans/OpenSans-Regular.ttf", 18);

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)graphics::WindowManager::getWindows()[0]->getWindowData().m_NativeWindow, true);
		ImGui_ImplOpenGL3_Init("#version 410");
		this->onAttach0();
	}
	void ImGuiLayer::onDetach()
	{
		this->onDetach0();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::setDarkThemecolors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
	void ImGuiLayer::onEvent(const events::Event& event)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([this](const events::AppRenderEvent& event)
			{
				this->begin();
				this->onEvent0(event);
				this->end(event.m_Delta);
				return false;
			});
		dispatcher.dispatch<events::AppUpdateEvent>([this](const events::AppUpdateEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::PathDroppedEvent>([this](const events::PathDroppedEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::KeyPressedEvent>([this](const events::KeyPressedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::KeyRepeatedEvent>([this](const events::KeyRepeatedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::KeyReleasedEvent>([this](const events::KeyReleasedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::CharTypedEvent>([this](const events::CharTypedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseMovedEvent>([this](const events::MouseMovedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseButtonPressedEvent>([this](const events::MouseButtonPressedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseButtonReleasedEvent>([this](const events::MouseButtonReleasedEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::MouseScrolledEvent>([this](const events::MouseScrolledEvent& event)
			{
				this->onEvent0(event);
				return this->m_BlockEvents;
			});
		dispatcher.dispatch<events::CursorEnteredEvent>([this](const events::CursorEnteredEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::CursorExitedEvent>([this](const events::CursorExitedEvent& event)
			{
				this->onEvent0(event);
				return false;
			});

		dispatcher.dispatch<events::WindowCloseEvent>([this](const events::WindowCloseEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowFocusEvent>([this](const events::WindowFocusEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowFocusLostEvent>([this](const events::WindowFocusLostEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowResizeEvent>([this](const events::WindowResizeEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowContentScaleEvent>([this](const events::WindowContentScaleEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowMoveEvent>([this](const events::WindowMoveEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowMinimizeEvent>([this](const events::WindowMinimizeEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowMaximizeEvent>([this](const events::WindowMaximizeEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowRestoreEvent>([this](const events::WindowRestoreEvent& event)
			{
				this->onEvent0(event);
				return false;
			});
		dispatcher.dispatch<events::WindowRefreshEvent>([this](const events::WindowRefreshEvent& event)
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
		io.DisplaySize = ImVec2(static_cast<float>(graphics::WindowManager::getWindows()[0]->getWindowData().m_Width),
			static_cast<float>(graphics::WindowManager::getWindows()[0]->getWindowData().m_Height));
		io.DeltaTime = deltaTime;

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			auto backupCurrentContext = graphics::WindowManager::getWindows()[0];
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			backupCurrentContext->makeCurrent();
		}
	}
} // namespace assec::editor
