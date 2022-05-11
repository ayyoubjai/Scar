#include "core/Engine.h"
#include "application/Application.h"
#include "core/Log.h"

#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"

#include "core/EntryPoint.h"
using namespace Scar;
class Editor :public Scar::Application {
	graphics::Shader* m_shader;
	graphics::Mesh* m_mesh;
	float var = 0.05f, nw = 0, nh = 0;
public:
	void Initialize() override {
		SCAR_DEBUG("Editor::Initialize()");
		
		float VertexBufferTest[] = {
			0.0f,1.0f,0.0f   ,0.5f,0.5f,1.0f,
			0.5f,0.5f,0.0f   ,0.9f,0.1f,0.1f,
			-0.5f,0.5f,0.0f  ,0.1f,0.3f,0.6f,
			0.5f,-0.5f,0.0f  ,0.9f,0.7f,0.0f,
			-0.5f,-0.5f,0.0f ,0.5f,0.6f,0.4f,
			0.0f,-1.0f,0.0f  ,0.8f,0.4f,0.0f

		};

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
	}

	void Update() override
	{
		SCAR_DEBUG("Editor::Update()");
		
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

	void Render() override {
		SCAR_DEBUG("Editor::Render()");
		
		m_shader->Bind();
		m_shader->SetVec2("ucolor", nw, nh);
		m_shader->UnBind();
		Engine::Get()->GetRenderManager()->Submit(new graphics::RenderMesh(m_mesh, m_shader));
		Engine::Get()->GetRenderManager()->Flush();
		
	}
};

Scar::Application* CreateApplication() {
	return new Editor();
}