#include "imguiWindow/imguiWindow.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_sdl.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "core/Engine.h"
#include "SDL2/SDL.h"


namespace Scar {
	void ImguiWindow::Create(const ImguiWindowProperties& iwps) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.ConfigWindowsMoveFromTitleBarOnly = iwps.MoveFromTitleBarOnly;

		if (iwps.IsDockingEnabled) {
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		}

		if (iwps.IsViewportsEnabled) {
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		}

		ImGui_ImplSDL2_InitForOpenGL(Engine::Get()->GetWindow()->GetSDLWindow(), Engine::Get()->GetWindow()->GetSDLGLContext());
		ImGui_ImplOpenGL3_Init("#version 330");

	}

	void ImguiWindow::ShutDown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiWindow::HandleSDLEvent(SDL_Event& event) {
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	void ImguiWindow::BeginRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(Engine::Get()->GetWindow()->GetSDLWindow());
		ImGui::NewFrame();
	}

	void ImguiWindow::EndRender() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			auto window = ENGINE()->GetWindow();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetSDLGLContext());
		}
	}

	bool ImguiWindow::WantCaptureMouse() {
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool ImguiWindow::WantCaptureKeyboard() {
		return ImGui::GetIO().WantCaptureKeyboard;
	}
}