#pragma once
#include "core/core.h"
#include "imguiWindow/ImguiWindow.h"
#include "graphics/FrameBuffer.h"
#include <string>
struct SDL_Window;
using SDL_GLContext = void*;
namespace Scar
{
	struct SCAR_API WindowProperties {
		std::string title;
		int x, y, w, h;
		int flags;
		int wMin, hMin;
		ImguiWindowProperties iwps;
		unsigned int ccr, ccg, ccb, cca;
		WindowProperties();
	};
	class Window
	{
	private:
		SDL_Window* m_window;
		SDL_GLContext m_glcontext;
		ImguiWindow m_imguiwindow;
		graphics::FrameBuffer* m_framebuffer;
	public:
		Window();
		~Window();
		void PumpEvents();
		bool Create(const WindowProperties& wps);
		void ShutDown();
		void BeginRender();
		void EndRender();
		void GetWindowSize(int& width, int& height);
		inline SDL_Window* GetSDLWindow() { return m_window; }
		inline SDL_GLContext GetSDLGLContext() { return m_glcontext; }
		inline graphics::FrameBuffer* GetFrameBuffer() { return m_framebuffer; }
	};
}
