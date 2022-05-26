#include "GameObj.h"
#include "glm/ext/matrix_transform.hpp"
#include "core/Engine.h"
#include "core/Log.h"
void GameObj::Render() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3{ m_pos.x,m_pos.y,0.0f });
	model = glm::scale(model, glm::vec3{ m_scale.x,m_scale.y,0.0f });
	m_shader->Bind();
	m_shader->SetMat4("model", model);
	m_shader->UnBind();
	ENGINE()->GetRenderManager()->Submit(new Scar::graphics::RenderMesh(m_mesh, m_shader));
	ENGINE()->GetRenderManager()->Flush();
}

void GameObj::Update(){}

bool GameObj::IsColliding(const glm::vec2& objPos, const glm::vec2& objSize,const glm::vec2& objScale)
{
	glm::vec2 rightObj1  = m_pos + glm::vec2{ m_scale.x*(m_size.x / 2.0f),0.0 };
	glm::vec2 leftObj1   = m_pos + glm::vec2{ m_scale.x*(-m_size.x / 2.0f),0.0 };
	glm::vec2 topObj1    = m_pos + glm::vec2{ 0.0,m_scale.y*(m_size.y / 2.0f) };
	glm::vec2 bottomObj1 = m_pos + glm::vec2{ 0.0,m_scale.y*(-m_size.y / 2.0f) };

	glm::vec2 rightObj2  = objPos + glm::vec2{ objScale.x*(objSize.x / 2.0f),0.0 };
	glm::vec2 leftObj2   = objPos + glm::vec2{ objScale.x*(-objSize.x / 2.0f),0.0 };
	glm::vec2 topObj2    = objPos + glm::vec2{ 0.0,objScale.y*(objSize.y / 2.0f) };
	glm::vec2 bottomObj2 = objPos + glm::vec2{ 0.0,objScale.y*(-objSize.y / 2.0f) };

	if ((rightObj1.x > leftObj2.x) && (leftObj1.x < rightObj2.x) && (topObj1.y > bottomObj2.y) && (bottomObj1.y < topObj2.y)){
		SCAR_DEBUG("collide \nball {},{}\nobj {},{}", m_pos.x, m_pos.y, objPos.x, objPos.y);
		return true;
	}
	return false;
}
