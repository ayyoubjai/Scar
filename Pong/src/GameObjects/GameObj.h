#pragma once
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "glm/glm.hpp"

class GameObj
{
protected:
	Scar::graphics::Mesh* m_mesh;
	Scar::graphics::Shader* m_shader;
	glm::vec2 m_pos;
	glm::vec2 m_scale;
	glm::vec2 m_size;

public:
	GameObj(Scar::graphics::Mesh* mesh,Scar::graphics::Shader* shader,const glm::vec2& pos,const glm::vec2& scale ,const glm::vec2& size)
		:m_mesh(mesh),m_shader(shader),m_pos(pos),m_size(size),m_scale(scale)
	{

	}

	void SetPos(const glm::vec2& pos) {
		m_pos = pos;
	}

	virtual void Move(const glm::vec2& by) {
		
		if ((m_pos.y < 0.75) && (m_pos.y > -0.75)) {
			m_pos += by;
		}
		if ((m_pos.y == 0.75) && (by.y < 0)) {
			m_pos += by;
		}else if ((m_pos.y == -0.75) && (by.y > 0)) {
			m_pos += by;
		}
	}

	const glm::vec2& GetPos() const {
		return m_pos;
	}

	const glm::vec2& GetSize() const {
		return m_size;
	}

	const glm::vec2& GetScale() const {
		return m_scale;
	}

	void Render();
	void Update();
	bool IsColliding(const glm::vec2& objPos, const glm::vec2& objSize,const glm::vec2& objScale);
};

