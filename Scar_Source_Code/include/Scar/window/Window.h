#pragma once
#include "core/core.h"
#include "imguiWindow/ImguiWindow.h"
#include "graphics/FrameBuffer.h"
#include "graphics/Vertex.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "glm/glm.hpp"
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
		float aspectRatio;
		ImguiWindowProperties iwps;
		float ccr, ccg, ccb, cca;
		WindowProperties();
	};
	class Window
	{
	private:
		WindowProperties m_windowProperties;
		SDL_Window* m_window;
		SDL_GLContext m_glcontext;
		ImguiWindow m_imguiwindow;
		graphics::FrameBuffer* m_framebuffer;
		bool m_renderScreen;
		graphics::VertexArray* m_va;
		graphics::Shader* m_shader;
		graphics::Texture* m_bg;

		float m_sizeTheoric;
		
	public:
		Window();
		~Window();
		void PumpEvents();
		bool Create(const WindowProperties& wps);
		void ShutDown();
		void BeginRender();
		void EndRender();
		void GetWindowSize(int& width, int& height);
		inline const glm::vec2& GetWindowSize() const { return { m_windowProperties.w,m_windowProperties.h }; }
		void RenderToScreen();
		void InitializeScreenRender();
		void HandleResize(int width,int height);
		inline SDL_Window* GetSDLWindow() { return m_window; }
		inline SDL_GLContext GetSDLGLContext() { return m_glcontext; }
		inline graphics::FrameBuffer* GetFrameBuffer() { return m_framebuffer; }
		inline void SetRenderScreen(bool enabled) { m_renderScreen = enabled; }
		inline bool GetRenderScreen() const { return m_renderScreen; }
		inline float GetAspectRatio() const { return m_windowProperties.aspectRatio; }
		inline float GetSizeTheoric() const { return m_sizeTheoric; }
		inline void SetSizeTheoric(const float& ST) { m_sizeTheoric = ST; }
	};
}
