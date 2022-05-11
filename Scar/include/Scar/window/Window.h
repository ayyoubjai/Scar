#pragma once
#include "core/core.h"
#include "imguiWindow/ImguiWindow.h"
struct SDL_Window;
using SDL_GLContext = void*;
namespace Scar
{
	class Window
	{
	private:
		SDL_Window* m_window;
		SDL_GLContext m_glcontext;
		ImguiWindow m_imguiwindow;
	public:
		Window();
		~Window();
		void PumpEvents();
		bool Create();
		void ShutDown();
		void BeginRender();
		void EndRender();
		void GetSize(int& width, int& height);
		inline SDL_Window* GetSDLWindow() { return m_window; }
		inline SDL_GLContext GetSDLGLContext() { return m_glcontext; }
	};
}
