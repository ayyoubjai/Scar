#include "window/Window.h"
#include "core/Engine.h"
#include "core/Log.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "events/MouseEvent.h"
#include "events/KeyEvent.h"
#include "vendor/imgui/imgui.h"
#include "graphics/Helpers.h"
#include "glm/ext/matrix_transform.hpp"
namespace Scar
{
	WindowProperties::WindowProperties() {
		title = "Scar app";
		x = SDL_WINDOWPOS_CENTERED;
		y = SDL_WINDOWPOS_CENTERED;
		w = 800; 
		h = 600;
		aspectRatio = 16.f / 9.f;
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
		ccr = 1;
		ccg = 1;
		ccb = 1;
		cca = 1;
	}
	Window::Window()
		:m_window(nullptr),m_renderScreen(false),m_sizeTheoric(500.0f)
	{

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
				case SDL_WINDOWEVENT: {
					if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
						m_windowProperties.w = e.window.data1;
						m_windowProperties.h = e.window.data2;
						m_windowProperties.aspectRatio = (float)m_windowProperties.h / m_windowProperties.w;
						Event::MouseEvent::SetScreenSize(e.window.data1, e.window.data2);
					}
				}
			}
			m_imguiwindow.HandleSDLEvent(e);
		}
		//if(!m_imguiwindow.WantCaptureKeyboard())
			Event::KeyEvent::Update();
		if(!m_imguiwindow.WantCaptureMouse())
			Event::MouseEvent::Update();
	}
	bool Window::Create(const WindowProperties& wps) {
		m_windowProperties = wps;
		m_window = SDL_CreateWindow(wps.title.c_str(), wps.x, wps.y, wps.w, wps.h, wps.flags);
		if (!m_window) {
			SCAR_ERROR("error creating window" , SDL_GetError() );
			return false;
		}
		//telleing sdl which opengl profile your are using and the version(minor and major) 
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
		InitializeScreenRender();
		Event::MouseEvent::SetScreenSize(wps.w, wps.h);
		//m_windowProperties.aspectRatio = (float)m_windowProperties.h / m_windowProperties.w;
		
		m_bg = new graphics::Texture("c:/dev/Scar/PFE/assets/bg.png");
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
		ENGINE()->GetRenderManager()->Push(new graphics::PushFrameBuffer(m_framebuffer));
		if (m_va->IsUploaded() && m_bg && m_shader) {
			ENGINE()->GetRenderManager()->Push(new graphics::RenderVertexArrayTextured(m_va, m_shader, m_bg));
		}
	}
	void Window::EndRender()
	{
		ENGINE()->GetRenderManager()->Push(new graphics::PopFrameBuffer(m_framebuffer));
		ENGINE()->GetRenderManager()->Execute();
		m_imguiwindow.BeginRender();
		if (m_renderScreen) {
			ENGINE()->GetApp()->UIRender();
			RenderToScreen();
		}
		else {
			ENGINE()->GetApp()->UIRender();
		}
		m_imguiwindow.EndRender();
		SDL_GL_SwapWindow(m_window);
	}
	void Window::GetWindowSize(int& width, int& height) {
		SDL_GetWindowSize(m_window, &width, &height);
	}
	
	void Window::RenderToScreen() {
		SCAR_ASSERT(m_va->IsUploaded(), "Attemting to Render with Invalid VertexArray - did you forget to call VertexArray::Upload()");
		if (m_va->IsUploaded()) {
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_va->Bind();
			m_shader->Bind();
			/*
			glm::vec2 scale{ m_framebuffer->GetWidth() / m_windowProperties.w,m_framebuffer->GetHeight() / m_windowProperties.h };

			glm::mat4 transform = glm::mat4{ 1.0f };
			transform = glm::scale(transform, glm::vec3{ scale.x,scale.y,0.0f });
			m_shader->SetMat4("model", transform);
			*/
			glBindTexture(GL_TEXTURE_2D, m_framebuffer->GetTexture());
			
			GlCall(glDrawElements(GL_TRIANGLES, m_va->GetElementCount(), GL_UNSIGNED_INT, (void*)0));
			
			glBindTexture(GL_TEXTURE_2D, 0);
			m_shader->UnBind();
			m_va->UnBind();
		}
		else {
			SCAR_WARN("RenderVertexArrayTextured::Execute() Vertex buffer is not uploaded - call VertexArray::Upload()");
		}
		
	}
	void Window::InitializeScreenRender() {
		m_va = new graphics::VertexArray();
		{
			graphics::VertexBuffer<float>* m_vb = new graphics::VertexBuffer<float>();
			m_vb->PushVertex({ -1.f,-1.f  ,0.f,0.f });
			m_vb->PushVertex({  1.f,-1.f  ,1.f,0.f });
			m_vb->PushVertex({  1.f, 1.f  ,1.f,1.f });
			m_vb->PushVertex({ -1.f, 1.f  ,0.f,1 });
			m_vb->SetLayout({ 2,2 });
			m_vb->Upload();
			m_va->PushBuffer(m_vb);
		}
		m_va->SetElements({ 0,1,2,0,2,3 });
		m_va->Upload();

		m_shader = new graphics::Shader("C:/dev/Scar/Scar/src/shaders/ScreenVertexShader.sh", "C:/dev/Scar/Scar/src/shaders/ScreenFragmentShader.sh");
		
	}

	void Window::HandleResize(int width, int height)
	{
		if (height > width) {
			m_framebuffer->SetWidth(width);
			m_framebuffer->SetHeight(width * (1.f / GetAspectRatio()));
		}
		else {
			m_framebuffer->SetHeight(height);
			m_framebuffer->SetWidth(height * m_framebuffer->GetHeight());
		}
	}
	
};