#pragma once
#include "core/core.h"
typedef union SDL_Event;
namespace Scar {
	struct SCAR_API ImguiWindowProperties {
		bool MoveFromTitleBarOnly = true;
		bool IsDockingEnabled = false;
		bool IsViewportsEnabled = false;
	};
	class ImguiWindow {
	public:
		ImguiWindow() {};
		~ImguiWindow() {};

		void Create(const ImguiWindowProperties& iwps);
		void ShutDown();
		void HandleSDLEvent(SDL_Event& event);
		void BeginRender();
		void EndRender();
		bool WantCaptureMouse();
		bool WantCaptureKeyboard();
	
	};
}