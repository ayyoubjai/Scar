#include "window/Window.h"
#include "core/Engine.h"
#include "core/Log.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "events/MouseEvent.h"
#include "events/KeyEvent.h"
#include "vendor/imgui/imgui.h"
namespace Scar 
{
	WindowProperties::WindowProperties() {
		title = "Scar app";
		x = SDL_WINDOWPOS_CENTERED;
		y = SDL_WINDOWPOS_CENTERED;
		w = 800; 
		h = 600;
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
		ccr = 1;
		ccg = 1;
		ccb = 1;
		cca = 1;
	}
	Window::Window()
		:m_window(nullptr) {

	}

	Window::~Window() {
		ShutDown();
	}

	void Window::PumpEvents() {
		SDL_Event e;
		//handles the envents queue
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: {
					ENGINE()->Quit();
					break;
				}
				
			}
			m_imguiwindow.HandleSDLEvent(e);
		}
		if(!m_imguiwindow.WantCaptureKeyboard())
			Event::KeyEvent::Update();
		if(!m_imguiwindow.WantCaptureMouse())
			Event::MouseEvent::Update();
	}
	bool Window::Create(const WindowProperties& wps) {
		m_window = SDL_CreateWindow(wps.title.c_str(), wps.x, wps.y, wps.w, wps.h, wps.flags);
		if (!m_window) {
			SCAR_ERROR("error creating window" , SDL_GetError() );
			return false;
		}
		//telleing sdl which opengl profile your are using and the version(minor and major) explecitly
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//set the minimum size of the window
		SDL_SetWindowMinimumSize(m_window, 200, 200);
		//create opengl context and store it
		m_glcontext = SDL_GL_CreateContext(m_window);

		if (!m_glcontext) {
			SCAR_ERROR("error fail to create an opengl context {}", SDL_GetError());
			return false;
		}

		gladLoadGLLoader(SDL_GL_GetProcAddress);
		m_framebuffer = new graphics::FrameBuffer(wps.w, wps.h);
		m_framebuffer->SetClearColor(wps.ccr, wps.ccg,wps.ccb, wps.cca);


		m_imguiwindow.Create(wps.iwps);
		return true;
	}

	void Window::ShutDown() {
		SDL_DestroyWindow(m_window);
		SDL_GL_DeleteContext(m_glcontext);
		m_window = nullptr;
	}
	void Window::BeginRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//ENGINE()->GetRenderManager()->Clear();
		ENGINE()->GetRenderManager()->Submit(new graphics::PushFrameBuffer(m_framebuffer));
	}
	void Window::EndRender()
	{
		ENGINE()->GetRenderManager()->Submit(new graphics::PopFrameBuffer(m_framebuffer));
		//i dont know why ??? now i know why hhhhh
		ENGINE()->GetRenderManager()->Flush();
		m_imguiwindow.BeginRender();
		//ImGui::ShowDemoWindow();
		ENGINE()->GetApp()->UIRender();
		m_imguiwindow.EndRender();
		SDL_GL_SwapWindow(m_window);
	}
	void Window::GetWindowSize(int& width, int& height) {
		SDL_GetWindowSize(m_window, &width, &height);
	}
};