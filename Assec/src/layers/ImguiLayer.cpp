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
			ref<assec::graphics::Window> backupCurrentContext = graphics::WindowManager::getWindows()[0];
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			backupCurrentContext->makeCurrent();
		}
	}
} // namespace assec::editor
