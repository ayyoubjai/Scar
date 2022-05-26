#include "core/EntryPoint.h"
#include "application/Application.h"
#include "GameObjects/GameObj.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "events/KeyEvent.h"
#include "Ball/Ball.h"
#include <random>
using namespace Scar;

class Pong :public Scar::Application {
	GameObj* m_leftpaddle,* m_rightpaddle;
	Ball* m_ball;
	graphics::Mesh* m_mesh, *m_meshBall;
	graphics::Shader* m_shader,*m_shaderBall;
	glm::vec3 m_step;
	bool m_collideleft = false;

public:
	void Initialize() override {
		float VertexBuffer[] = {
			-0.0625f,-0.25f,0.0f,
			0.0625f, -0.25f,0.0f,
			0.0625f,  0.25f,0.0f,
			-0.0625f, 0.25f,0.0f
		};
		float VertexBufferBall[] = {
			-0.125f,-0.125f,0.0f,
			0.125f,-0.125f,0.0f,
			0.125f,0.125f,0.0f,
			-0.125f,0.125f,0.0f
		};
		unsigned int ElementBuffer[] = {
			0,1,2,
			0,2,3
		};
		m_mesh = new graphics::Mesh(VertexBuffer, 4, 3, ElementBuffer, 6);
		m_meshBall = new graphics::Mesh(VertexBufferBall, 4, 3, ElementBuffer, 6);
		m_shader = new graphics::Shader("C:/dev/Scar/Pong/src/shaders/VertexShader.sh","C:/dev/Scar/Pong/src/shaders/FragmentShader.sh");
		m_shaderBall = new graphics::Shader("C:/dev/Scar/Pong/src/shaders/VertexShader.sh","C:/dev/Scar/Pong/src/shaders/BallFragmentShader.sh");

		m_leftpaddle = new GameObj(m_mesh, m_shader, { -1.0+0.0625,0.0 }, { 1.0,1.0 },{0.125,0.5});
		m_rightpaddle = new GameObj(m_mesh, m_shader, {1.0-0.0625,0.0}, {1.0,1.0}, { 0.125,0.5 });
		m_ball = new Ball(m_meshBall, m_shaderBall, { 0.0,0.0 }, { 0.6,1.00 }, { 0.25,0.25 });
		
		m_step = glm::vec3{ 0.0f,0.25f,0.0f };
		m_ball->SetVelocity({0.0005,0.0004 });
	}													

	void Render() override {
		m_rightpaddle->Render();
		m_leftpaddle->Render();
		m_ball->Render();
	}
	
	void UIRender() override {
		if (ImGui::Begin("Game View")) {
			if (ImGui::IsWindowHovered()) {
				ImGui::CaptureMouseFromApp(false);
				ImGui::CaptureKeyboardFromApp(false);
			}
			else {
				ImGui::CaptureMouseFromApp(true);
				ImGui::CaptureKeyboardFromApp(true);
			}
			ImGui::Image((void*)ENGINE()->GetWindow()->GetFrameBuffer()->GetTexture(), { 750,450 },{0.0,1.0},{1.0,0.0});
		}
		ImGui::End();
	}
	
	void Update() override {
		
		m_ball->Move(m_ball->GetVelocity());

		if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_X)) {
			m_leftpaddle->Move(m_step);
		}
		else if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_LALT)) {
			m_leftpaddle->Move(-m_step);
		}
		else if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_UP)) {
			m_rightpaddle->Move(m_step);
		}
		else if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_DOWN)) {
			m_rightpaddle->Move(-m_step);
		}
		
		if ((m_ball->IsColliding(m_leftpaddle->GetPos(), m_leftpaddle->GetSize(),m_leftpaddle->GetScale()))&&m_collideleft) {
			m_collideleft = false;
			m_ball->FlipVeloX();
			m_ball->SetVelocity(m_ball->GetVelocity() + glm::vec2{ 0.0002,0.0002 });
			
		}
		if (m_ball->IsColliding(m_rightpaddle->GetPos(), m_rightpaddle->GetSize(),m_rightpaddle->GetScale())&&!m_collideleft) {
			m_collideleft = true;
			m_ball->FlipVeloX();
			m_ball->SetVelocity(m_ball->GetVelocity() + glm::vec2{ -0.0002,0.0002 });
		}

		if ((m_ball->GetPos().y+0.125 >= 1) || (m_ball->GetPos().y - 0.125 <= -1))
			m_ball->FlipVeloY();
		
	}
	
	void ShutDown() override {

	}
	 
	WindowProperties CreateWindowProperties() override {
		WindowProperties wps;
		wps.ccr = 0.0;
		wps.ccg = 1.0;
		wps.ccb = 0.0;
		wps.cca = 1.0;
		wps.iwps.IsDockingEnabled = true;
		wps.iwps.IsViewportsEnabled = true;
		return wps;
	}

};

Scar::Application* CreateApplication() {
	return new Pong();
}