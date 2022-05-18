#pragma once
#include "core/core.h"
#include "imguiWindow/ImguiWindow.h"
<<<<<<< HEAD
#include "graphics/FrameBuffer.h"
#include <string>
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
struct SDL_Window;
using SDL_GLContext = void*;
namespace Scar
{
<<<<<<< HEAD
	struct SCAR_API WindowProperties {
		std::string title;
		int x, y, w, h;
		int flags;
		int wMin, hMin;
		ImguiWindowProperties iwps;
		unsigned int ccr, ccg, ccb, cca;
		WindowProperties();
	};
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	class Window
	{
	private:
		SDL_Window* m_window;
		SDL_GLContext m_glcontext;
		ImguiWindow m_imguiwindow;
<<<<<<< HEAD
		graphics::FrameBuffer* m_framebuffer;
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	public:
		Window();
		~Window();
		void PumpEvents();
<<<<<<< HEAD
		bool Create(const WindowProperties& wps);
		void ShutDown();
		void BeginRender();
		void EndRender();
		void GetWindowSize(int& width, int& height);
		inline SDL_Window* GetSDLWindow() { return m_window; }
		inline SDL_GLContext GetSDLGLContext() { return m_glcontext; }
		inline graphics::FrameBuffer* GetFrameBuffer() { return m_framebuffer; }
=======
		bool Create();
		void ShutDown();
		void BeginRender();
		void EndRender();
		void GetSize(int& width, int& height);
		inline SDL_Window* GetSDLWindow() { return m_window; }
		inline SDL_GLContext GetSDLGLContext() { return m_glcontext; }
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	};
}
