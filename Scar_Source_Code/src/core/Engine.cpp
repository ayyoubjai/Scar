#include<iostream>
#include<mutex>
#include <memory>
#include "core/Engine.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "core/Log.h"
#include "graphics/Shader.h"
#include "events/MouseEvent.h"
#include "events/KeyEvent.h"
#include "application/Application.h"


namespace Scar {
	Engine::Engine():m_running(false),m_initialized(false),m_app(nullptr) {

	}

	Engine* Engine::Get() {
		static std::mutex s_mutex;
		static Engine* s_instance = nullptr;
		std::lock_guard<std::mutex> lock(s_mutex);
		return (s_instance == nullptr) ? s_instance=new Engine() : s_instance;
	}

	bool Engine::Initialize(Application* app) {
		int ret = false;
		SCAR_ASSERT(!m_initialized, "attempt to call Engine::Initialize more tan once");
		if (!m_initialized) {
			SCAR_ASSERT(!m_app, "Attempting to call Scar::Run when a valid app alredy exists");
			m_app = app;
			m_logger.Initialize();
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
				SCAR_ERROR("error initializing sdl2 {}", SDL_GetError());
				ret = false;
			}
			else {
				SDL_version version;
				SDL_VERSION(&version);
				SCAR_INFO("SDL version : {}.{}.{}", (int)version.major, (int)version.minor, (int)version.patch);
				auto wps = app->CreateWindowProperties();
				if (!m_window.Create(wps)) {
					ret = false;
				}
				else {
					
					//everything is good
					m_running = true;
					m_initialized = true;
					ret = true;
					SCAR_INFO("the engine is succesfully initialized");

					//Initialize all managers here
					m_renderer.Initialize();

					//Initialize all Events
					Event::MouseEvent::Initialize();
					Event::KeyEvent::Initialize();

					//Print Infos
					Scar::GetInfo();

					//Initialize Client
					m_app->Initialize();
					
				}
			}
			if (!ret) {
				SCAR_ERROR("fail init the engine");
				ShutDown();
			}
		}
		return ret;
	}

	void Engine::Quit() {
		m_running = false;
	}

	Window* Engine::GetWindow()
	{
		return &m_window;
	}

	void Engine::Run() {
		
		m_renderer.SetWireframeMode(false);
		
		while (m_running) {
			//handle events queue in every eteration
			Update();
			Render();
		}
		
	}

	void Engine::ShutDown() {
		m_app->ShutDown();
		m_renderer.ShutDown();
		m_window.ShutDown();
		m_logger.ShutDown();
		SDL_Quit();
		SCAR_INFO("The engine is shutdown successfully");
	}

	Managers::RenderManager* Engine::GetRenderManager() {
		return &m_renderer;
	}

	void Engine::Render()
	{
		m_window.BeginRender();
		m_app->Render();
		m_window.EndRender();
	}

	void Engine::Update() {
		m_window.PumpEvents();
		m_app->Update();
	}


	void GetInfo() {
		SCAR_INFO("ScarEngine version {}.{}", 0, 1);
#if defined SC_DEBUG
		SCAR_INFO("Configuration : Debug\n") ;
#elif defined SC_RELEASE
		SCAR_INFO("Configuration : Release\n") ;
#endif
	}

	

}