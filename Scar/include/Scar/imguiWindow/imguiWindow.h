#pragma once
typedef union SDL_Event;
namespace Scar {
	class ImguiWindow {
	public:
		ImguiWindow() {};
		~ImguiWindow() {};

		void Create();
		void ShutDown();
		void HandleSDLEvent(SDL_Event& event);
		void BeginRender();
		void EndRender();
	};
}