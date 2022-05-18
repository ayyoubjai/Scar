#pragma once
#include "core/core.h"
#include "window/Window.h"
#include "managers/LogManager.h"
#include "managers/RenderManager.h"
#include "application/Application.h"
<<<<<<< HEAD

=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
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
<<<<<<< HEAD
		inline Application* GetApp() { return m_app; }
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	};
	SCAR_API void GetInfo();
}

<<<<<<< HEAD
#define ENGINE() Engine::Get()
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4

