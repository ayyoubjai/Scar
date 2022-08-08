#pragma once
#include "core/core.h"
#include "window/Window.h"
#include "managers/LogManager.h"
#include "managers/RenderManager.h"
#include "application/Application.h"

namespace Scar {

	class SCAR_API Engine
	{
	private:
		Engine();
		Window m_window;
		Managers::LogManager m_logger;
		Managers::RenderManager m_renderer;
		bool m_running;
		bool m_initialized;
		Application* m_app;
		
	public:
		static Engine* Get();
		Managers::RenderManager* GetRenderManager();
		Window* GetWindow();
		void Run();
		bool Initialize(Application* application);
		void ShutDown();
		void Quit();
		void Update();
		void Render();
		inline Application* GetApp() { return m_app; }
	};
	SCAR_API void GetInfo();
}

#define ENGINE() Scar::Engine::Get()

