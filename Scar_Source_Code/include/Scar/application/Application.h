#pragma once
#include "core/core.h"
#include "vendor/imgui/imgui.h"
#include "window/Window.h"
namespace Scar {
	class SCAR_API Application {
	public:
		Application(){}
		~Application(){}

		virtual void Initialize(){}
		virtual void ShutDown(){}
		virtual void Update(){}
		virtual void Render(){}
		virtual void UIRender() { ImGui::ShowDemoWindow(); }
		virtual WindowProperties CreateWindowProperties() { return WindowProperties(); }
	};
}