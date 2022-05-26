#pragma once
#include "GameObjects/GameObj.h"
#include "graphics/Mesh.h"
#include "glm/glm.hpp"

class Ball:public GameObj
{
	glm::vec2 m_velocity;
public:
	Ball(Scar::graphics::Mesh* mesh,Scar::graphics::Shader* shader,const glm::vec2& pos,const glm::vec2& scale, const glm::vec2& size )
		:GameObj(mesh,shader,pos, scale,size),m_velocity(0)
	{}
	void SetVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
	glm::vec2 GetVelocity() { return m_velocity; }
	void FlipVeloX() { m_velocity.x *= -1; }
	void FlipVeloY() { m_velocity.y *= -1; }
	void Move(const glm::vec2& by) override {
		m_pos += by;
	}
};

