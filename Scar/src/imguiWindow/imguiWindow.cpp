#include "imguiWindow/imguiWindow.h"
#include "vendor/imgui/imgui.h"

#include "vendor/imgui/imgui_impl_sdl.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "core/Engine.h"

namespace Scar {
	void ImguiWindow::Create() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
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
	}
}