#pragma once
<<<<<<< HEAD
#include "core/core.h"
typedef union SDL_Event;
namespace Scar {
	struct SCAR_API ImguiWindowProperties {
		bool MoveFromTitleBarOnly = true;
		bool IsDockingEnabled = false;
		bool IsViewportsEnabled = false;
	};
=======
typedef union SDL_Event;
namespace Scar {
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	class ImguiWindow {
	public:
		ImguiWindow() {};
		~ImguiWindow() {};

<<<<<<< HEAD
		void Create(const ImguiWindowProperties& iwps);
=======
		void Create();
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
		void ShutDown();
		void HandleSDLEvent(SDL_Event& event);
		void BeginRender();
		void EndRender();
<<<<<<< HEAD
		bool WantCaptureMouse();
		bool WantCaptureKeyboard();
	
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	};
}