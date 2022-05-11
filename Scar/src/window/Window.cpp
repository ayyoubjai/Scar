#include<iostream>
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
					Engine::Get()->Quit();
					break;
				}
				
			}
			m_imguiwindow.HandleSDLEvent(e);
		}
		Event::KeyEvent::Update();
		Event::MouseEvent::Update();
	}
	bool Window::Create() {
		m_window = SDL_CreateWindow("Scar app", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
		if (!m_window) {
			std::cout << "error creating window" << SDL_GetError() << std::endl;
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
		m_imguiwindow.Create();
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
	}
	void Window::EndRender()
	{
		m_imguiwindow.BeginRender();
		ImGui::ShowDemoWindow();
		m_imguiwindow.EndRender();
		SDL_GL_SwapWindow(m_window);
	}
	void Window::GetSize(int& width, int& height) {
		SDL_GetWindowSize(m_window, &width, &height);
	}
};