#include "core/Engine.h"
#include "application/Application.h"
#include "core/Log.h"
<<<<<<< HEAD
=======

>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
<<<<<<< HEAD
#include "core/EntryPoint.h"
#include "vendor/imgui/imgui.h"
=======

#include "core/EntryPoint.h"
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
using namespace Scar;
class Editor :public Scar::Application {
	graphics::Shader* m_shader;
	graphics::Mesh* m_mesh;
<<<<<<< HEAD
	graphics::Texture* m_texture;
	float var = 0.05f, nw = 0, nh = 0;
public:
	void Initialize() override {
		/*
=======
	float var = 0.05f, nw = 0, nh = 0;
public:
	void Initialize() override {
		SCAR_DEBUG("Editor::Initialize()");
		
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
		float VertexBufferTest[] = {
			0.0f,1.0f,0.0f   ,0.5f,0.5f,1.0f,
			0.5f,0.5f,0.0f   ,0.9f,0.1f,0.1f,
			-0.5f,0.5f,0.0f  ,0.1f,0.3f,0.6f,
			0.5f,-0.5f,0.0f  ,0.9f,0.7f,0.0f,
			-0.5f,-0.5f,0.0f ,0.5f,0.6f,0.4f,
			0.0f,-1.0f,0.0f  ,0.8f,0.4f,0.0f

		};
<<<<<<< HEAD
		*/
		float VertexBufferTest[] = {
			0.5f, 0.5f, 0.0f		, 1.0f, 0.0f, 0.0f		, 1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f		, 0.0f, 1.0f, 0.0f		, 1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f		, 0.0f, 0.0f, 1.0f		, 0.0f, 0.0f,   // bottom left
			-0.5f, 0.5f, 0.0f		, 1.0f, 1.0f, 0.0f		, 0.0f, 1.0f    // top left 
		};
		unsigned int ElementBufferTest[] = {
			0,1,2,
			2,3,0
		};
		m_mesh = new graphics::Mesh(VertexBufferTest, 4, 8, ElementBufferTest, sizeof(ElementBufferTest) / sizeof(unsigned int));
		m_shader = new graphics::Shader("C:/dev/Scar/Scar/src/shaders/VertexShader.sh", "C:/dev/Scar/Scar/src/shaders/FragmentShader.sh");
		m_texture = new graphics::Texture("C:/dev/Scar/Scar/include/Scar/assets/container.jpg");
		SCAR_WARN("HELLO");
	}

	void ShutDown() override {

=======

		unsigned int ElementBufferTest[] = {
			0,1,2,
			1,2,3,
			2,3,4,
			3,4,5,
		};
		m_mesh = new graphics::Mesh(VertexBufferTest, 6, 6, ElementBufferTest, sizeof(ElementBufferTest) / sizeof(unsigned int));
		m_shader = new graphics::Shader("C:/dev/Scar/Scar/src/shaders/VertexShader.sh", "C:/dev/Scar/Scar/src/shaders/FragmentShader.sh");
		
	}

	void ShutDown() override {
		SCAR_DEBUG("Editor::ShutDown()");
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	}

	void Update() override
	{
<<<<<<< HEAD
		
=======
		SCAR_DEBUG("Editor::Update()");
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
		
		if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_RIGHT)) {
			//SCAR_INFO(">>>>>>>>>>>>>>>>>>>>>>");
			nw += var;
		}
		else if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_LEFT)) {
			//SCAR_INFO("<<<<<<<<<<<<<<<<<<<<<<");
			nw -= var;
		}
		else if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_UP)) {
			//SCAR_INFO("AAAAAAAAAAAAAAAAAAAAAAA");
			nh += var;
		}
		else if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_DOWN)) {
			//SCAR_INFO("VVVVVVVVVVVVVVVVVVVVVVV");
			nh -= var;
		}
		
	} 

<<<<<<< HEAD
	void Render() override {		
		m_shader->Bind();
		m_shader->SetVec2("ucolor", nw, nh);
		m_shader->UnBind();
		//Engine::Get()->GetRenderManager()->Submit(new graphics::RenderMesh(m_mesh, m_shader));
		Engine::Get()->GetRenderManager()->Submit(new graphics::RenderTexture(m_mesh, m_shader,m_texture));
		Engine::Get()->GetRenderManager()->Flush();
	}
	
	void UIRender() override {
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		if (ImGui::Begin("Test X")) {
			ImGui::DragFloat("X", &nw, var);
		}
		ImGui::End();
		if (ImGui::Begin("Test Y")) {
			ImGui::DragFloat("Y", &nh, var);
		}
		ImGui::End();
		if (ImGui::Begin("Game View")) {
			if (ImGui::IsWindowHovered()) {
				ImGui::CaptureMouseFromApp(false);
				ImGui::CaptureKeyboardFromApp(false);
			}
			else {
				ImGui::CaptureMouseFromApp(true);
				ImGui::CaptureKeyboardFromApp(true);
			}
			ImGui::Image((void*)ENGINE()->GetWindow()->GetFrameBuffer()->GetTexture(), { 250,200 });
		}
		ImGui::End();
	}

	WindowProperties CreateWindowProperties() {
		WindowProperties wps;
		wps.title = "Scar Editor";
		wps.iwps.IsViewportsEnabled = true;
		wps.iwps.IsDockingEnabled = true;
		wps.ccr = 0;
		wps.ccg = 1;
		wps.ccb = 0;
		wps.cca = 1;
		return wps;
	}
	
=======
	void Render() override {
		SCAR_DEBUG("Editor::Render()");
		
		m_shader->Bind();
		m_shader->SetVec2("ucolor", nw, nh);
		m_shader->UnBind();
		Engine::Get()->GetRenderManager()->Submit(new graphics::RenderMesh(m_mesh, m_shader));
		Engine::Get()->GetRenderManager()->Flush();
		
	}
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
};

Scar::Application* CreateApplication() {
	return new Editor();
}