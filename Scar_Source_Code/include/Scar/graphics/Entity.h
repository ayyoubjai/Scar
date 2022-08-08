#pragma once

#include "core/core.h"
#include "glm/glm.hpp"
#include "graphics/Shader.h"
#include "graphics/Vertex.h"
#include "graphics/Texture.h"

namespace Scar::graphics {
	class SCAR_API Entity {
	public:
		enum EntityType :unsigned int
		{
			SQUARE_FILLED,
			DISK,
			TRIANGLE,
			DIMOND,
			LINE,
			SQUARE,DOOR,SINK,DESK,TOILET,CAR,STOVE,SOFA,CHAIR,DINING_TABLE,ROUND_TABLE,BED
		};
	protected:
		
		EntityType m_type;
		unsigned int ID;
		glm::vec4 m_color;
		glm::vec2 m_pos;
		glm::vec2 m_size;
		glm::vec2 m_scale;
		glm::mat4 m_transform;
		bool m_filled = true;
		float m_rot;
		VertexArray* m_vertexArray;
		Texture* m_texture;
		
	public:
		Entity();
		Entity(const glm::vec2& pos,const glm::vec2& size,const glm::vec2& scale,const glm::mat4& transform=glm::mat4{1.0f});
		void SetID(const unsigned& id);
		unsigned int GetID() const;
		void SetTexture(Texture* texture);
		void SetVertexArray(VertexArray* va);
		bool IsSelected() const;
		inline const glm::vec2& GetPos() const { return m_pos; }
		inline const glm::vec2& GetSize() const { return m_size; }
		inline const glm::vec2& GetScale() const { return m_scale; }
		inline const glm::vec4& GetColor() const { return m_color; }
		inline float& GetPosX() { return m_pos.x; }
		inline float& GetPosY() { return m_pos.y; }
		virtual inline const float& GetRotation() const { return m_rot; }
		virtual inline void SetRotation(float rot) { m_rot = rot; }
		virtual inline EntityType GetType() const { return m_type; }
		inline void SetPos(float x, float y) { m_pos = glm::vec2{ x,y }; }
		inline void SetSize(float width, float height) { m_size = glm::vec2{width,height}; }
		inline void SetColor(float r,float g, float b,float w) { m_color = glm::vec4{r,g,b,w}; }
		inline void SetScale(float x, float y) { m_scale = glm::vec2{ x, y }; }
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual bool ClickCollision() = 0;
		virtual const char* Info() = 0;
		
	};

	class SCAR_API Dimond :public Entity {
		Shader m_shader;
	public:
		Dimond(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform = glm::mat4{ 1.0f });
		~Dimond();
		void Render();
		void Update();
		bool ClickCollision();
		const char* Info();
	};

	class SCAR_API SquareFilled:public Entity {
		Shader m_shader;
	public:
		SquareFilled(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform=glm::mat4{1.0f});
		~SquareFilled();
		void Render();
		void Update();
		bool ClickCollision();
		const char* Info();
	};

	class SCAR_API Square :public Entity {
		Shader m_shader;
	public:
		Square(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform = glm::mat4{ 1.0f });
		~Square();
		void Render();
		void Update();
		bool ClickCollision();
		const char* Info() override;
	};

	class SCAR_API Disk :public Entity {
		Shader m_shader;
	public:
		Disk(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform = glm::mat4{ 1.0f });
		~Disk();
		void Render();
		void Update();
		bool ClickCollision();
		const char* Info() override;
	};

	class SCAR_API Triangle :public Entity {
		Shader m_shader;
	public:
		Triangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform = glm::mat4{ 1.0f });
		~Triangle();
		void Render() override;
		void Update() override;
		bool ClickCollision();
		const char* Info() override;
	};

	class SCAR_API Icon :public Entity {
		Shader m_shader;
	public:
		Icon(EntityType type ,const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform = glm::mat4{ 1.0f });
		~Icon();
		void Render() override;
		void Update() override;
		bool ClickCollision();
		const char* Info() override;
	};

	class SCAR_API Line :public Entity {
		Shader m_shader;
	public:
		Line(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform = glm::mat4{ 1.0f });
		~Line();
		void Render() override;
		void Update() override;
		bool ClickCollision();
		const char* Info() override;
	};
}