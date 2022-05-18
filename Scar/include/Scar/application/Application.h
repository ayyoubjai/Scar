#pragma once
#include "core/core.h"
<<<<<<< HEAD
#include "vendor/imgui/imgui.h"
#include "window/Window.h"
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
namespace Scar {
	class SCAR_API Application {
	public:
		Application(){}
		~Application(){}

		virtual void Initialize(){}
		virtual void ShutDown(){}
		virtual void Update(){}
		virtual void Render(){}
<<<<<<< HEAD
		virtual void UIRender() { ImGui::ShowDemoWindow(); }
		virtual WindowProperties CreateWindowProperties() { return WindowProperties(); }
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	};
}