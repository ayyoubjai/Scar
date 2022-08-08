#include "graphics/Entity.h"
#include "managers/EntityManager.h"
#include "glm/ext/matrix_transform.hpp"
#include "events/MouseEvent.h"
#include "core/Engine.h"
#include "core/Log.h"
#include "graphics/RenderCommands.h"
#include <cmath>
namespace Scar::graphics {
	Entity::Entity()
		:ID{ 0 }, m_rot{0.0f}, m_color{ 1.0f,0.0f,0.0f,1.0f }, m_pos{ 0.0f,0.0f }, m_scale{ 0.0f,0.0f }, m_size{ 0.0f,0.0f }, m_transform{ glm::mat4{1.0f} }, m_vertexArray{ nullptr }, m_texture{ nullptr }
	{

	}

	Entity::Entity(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale ,const glm::mat4& transform) 
		: ID{ 0 }, m_rot{0.0f}, m_color{ 40.f/255.f,40.f / 255.f,40.f / 255.f,1.0f }, m_pos{ pos }, m_size{ size }, m_scale{ scale }, m_transform{ transform }, m_vertexArray{ nullptr }, m_texture{ nullptr }
	{

	}

	bool Entity::IsSelected() const {
		return (this == EntityMgr()->GetEntitySelected()) ? true : false;
	}
	/*
	void Entity::Update() {
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_size = { m_size.x * (ST / WindowSize.x) ,m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		if (!ENGINE()->GetWindow()->GetRenderScreen()) {
			m_shader.SetMat4("proj", glm::mat4{ 1.0f });//EntityMgr()->GetCamera()->GetProjectionMatrix());
			m_shader.SetMat4("view", glm::mat4{ 1.0f });//EntityMgr()->GetCamera()->GetViewMatrix());
		}
		else {
			m_shader.SetMat4("proj", glm::mat4{1.0f});
			m_shader.SetMat4("view", glm::mat4{ 1.0f });
		}
		
		
		m_shader.UnBind();
	}
	*/
	
	void Entity::SetTexture(Texture* texture)
	{
		m_texture = texture;
	}
	void Entity::SetVertexArray(VertexArray* va)
	{
		m_vertexArray = va;
	}

	void Entity::SetID(const unsigned& id) {
		ID = id;
	}
	unsigned int Entity::GetID() const {
		return ID;
	}

	//Begin class Square
	const char* Square::Info() {
		return "Square";
	}

	void Square::Render() {
		if (m_texture != nullptr) {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArrayTextured(m_vertexArray, &m_shader, m_texture));
		}
		else {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArray(m_vertexArray, &m_shader));
		}
		
	}
	Square::Square(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform)
		: Entity(pos,size,scale,transform), m_shader("C:/dev/Scar/PFE/src/shaders/SquareVertexShader.sh", "C:/dev/Scar/PFE/src/shaders/SquareFragmentShader.sh")
	{
		m_type = SQUARE;
	}

	Square::~Square() {
		
	}

	void Square::Update() {
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();
		
		m_transform = glm::rotate(m_transform, glm::radians(m_rot), { 0,0,1 });
		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		
		m_size = { m_scale.x*m_size.x * (ST / WindowSize.x) ,m_scale.y*m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		m_shader.UnBind();
	}

	bool Square::ClickCollision() {
		auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
		auto right = this->GetPos().x + (this->GetSize().x / 2);
		auto left = this->GetPos().x - (this->GetSize().x / 2);
		auto up = this->GetPos().y + (this->GetSize().y / 2);
		auto down = this->GetPos().y - (this->GetSize().y / 2);
		if ((mousePos.x >= left) && (mousePos.x <= right) && (mousePos.y <= up) && (mousePos.y >= down)) {
			return true;
		}
		return false;
	}
	//End Square class 

	//Begin class Square
	const char* Disk::Info() {
		return "Disk";
	}
	Disk::Disk(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform)
		: Entity(pos, size, scale, transform), m_shader("C:/dev/Scar/PFE/src/shaders/VertexShader.sh", "C:/dev/Scar/PFE/src/shaders/BallFragmentShader.sh")
	{
		m_type = DISK;
	}

	Disk::~Disk() {

	}

	void Disk::Update() {
		//temp we will use the square update
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_size = { m_scale.x*m_size.x * (ST / WindowSize.x) ,m_scale.y*m_size.y * (ST / WindowSize.y) };

		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		
		m_shader.UnBind();
	}
	void Disk::Render() {
		if (m_texture != nullptr) {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArrayTextured(m_vertexArray, &m_shader, m_texture));
		}
		else {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArray(m_vertexArray, &m_shader));
		}
	}
	bool Disk::ClickCollision() {
		auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
		//a=m_pos b=mousePos c=a-b |c| = sqrt(c.x*c.x+c.y+c.y)
		//if(m_size == 2|c|) 
		auto distance = sqrt(pow(m_pos.x - mousePos.x, 2) + pow(m_pos.y - mousePos.y, 2));
		SCAR_DEBUG("distance : {}",distance);
		SCAR_DEBUG("rayon : {}", m_size.x);
		if (distance <= m_size.x/2) {
			return true;
		}
		return false;
	}
	//End class Square

	//Begin class SquareFilled
	const char* SquareFilled::Info() {
		return "Square Filled";
	}
	SquareFilled::SquareFilled(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform)
		: Entity(pos, size, scale, transform), m_shader("C:/dev/Scar/PFE/src/shaders/VertexShader.sh", "C:/dev/Scar/PFE/src/shaders/FragmentShader.sh")
	{
		m_type = SQUARE_FILLED;
	}

	SquareFilled::~SquareFilled() {

	}

	void SquareFilled::Update() {
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_transform = glm::rotate(m_transform, glm::radians(m_rot), { 0,0,1 });
		m_size = { m_scale.x * m_size.x * (ST / WindowSize.x) ,m_scale.y * m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		
		m_shader.UnBind();
	}

	bool SquareFilled::ClickCollision() {
		auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
		auto right = this->GetPos().x + (this->GetSize().x / 2);
		auto left = this->GetPos().x - (this->GetSize().x / 2);
		auto up = this->GetPos().y + (this->GetSize().y / 2);
		auto down = this->GetPos().y - (this->GetSize().y / 2);
		if ((mousePos.x >= left) && (mousePos.x <= right) && (mousePos.y <= up) && (mousePos.y >= down)) {
			return true;
		}
		return false;
	}

	void SquareFilled::Render() {
		if (m_texture != nullptr) {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArrayTextured(m_vertexArray, &m_shader, m_texture));
		}
		else {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArray(m_vertexArray, &m_shader));
		}

	}
	//End SquareFilled class

	//Begin Triangle class
	Triangle::Triangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform) 
		: Entity(pos, size, scale, transform), m_shader("C:/dev/Scar/PFE/src/shaders/VertexShader.sh", "C:/dev/Scar/PFE/src/shaders/FragmentShader.sh")
	{
		m_type = TRIANGLE;
	}

	Triangle::~Triangle() {

	}

	void Triangle::Render() {
		if (m_texture != nullptr) {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArrayTextured(m_vertexArray, &m_shader, m_texture));
		}
		else {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArray(m_vertexArray, &m_shader));
		}

	}

	void Triangle::Update() {
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_transform = glm::rotate(m_transform, glm::radians(m_rot), { 0,0,1 });
		m_size = { m_scale.x * m_size.x * (ST / WindowSize.x) ,m_scale.y * m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		m_shader.UnBind();
	}

	bool Triangle::ClickCollision() {
		auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
		auto right = this->GetPos().x + (this->GetSize().x / 2);
		auto left = this->GetPos().x - (this->GetSize().x / 2);
		auto up = this->GetPos().y + (this->GetSize().y / 2);
		auto down = this->GetPos().y - (this->GetSize().y / 2);
		if ((mousePos.x >= left) && (mousePos.x <= right) && (mousePos.y <= up) && (mousePos.y >= down)) {
			return true;
		}
		return false;
	}

	const char* Triangle::Info() {
		return "Triangle";
	}

	//End Triangle class

	//Begin class Door
	Icon::Icon(EntityType type,const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform)
		: Entity(pos, size, scale, transform), m_shader("C:/dev/Scar/PFE/src/shaders/SquareVertexShader.sh", "C:/dev/Scar/PFE/src/shaders/SquareFragmentShader.sh")
	{
		m_type = type;
	}

	Icon::~Icon() {

	}

	void Icon::Render() {
		if (m_texture != nullptr) {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArrayTextured(m_vertexArray, &m_shader, m_texture));
		}
		else {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArray(m_vertexArray, &m_shader));
		}

	}

	const char* Icon::Info() {
		switch (this->m_type) {
		case graphics::Entity::SINK: {
			return "Sink";
		}
		case graphics::Entity::TOILET: {
			return "Toilet";
		}
		case graphics::Entity::SOFA: {
			return "Sofa";
		}
		case graphics::Entity::DOOR: {
			return "Door";
		}
		case graphics::Entity::STOVE: {
			return "Stove";
		}
		case graphics::Entity::DESK: {
			return "Desk";
		}
		case graphics::Entity::CAR: {
			return "Car";
		}
		case graphics::Entity::CHAIR: {
			return "Chair";
		}
		case graphics::Entity::ROUND_TABLE: {
			return "Round Table";
		}
		case graphics::Entity::DINING_TABLE: {
			return "Dining Table";
		}
		case graphics::Entity::BED: {
			return "Bed";
		}
		}
	}

	void Icon::Update() {
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_transform = glm::rotate(m_transform, glm::radians(m_rot), { 0,0,1 });
		m_size = { m_scale.x * m_size.x * (ST / WindowSize.x) ,m_scale.y * m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		
		m_shader.UnBind();
	}

	bool Icon::ClickCollision() {
		auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
		auto right = this->GetPos().x + (this->GetSize().x / 2);
		auto left = this->GetPos().x - (this->GetSize().x / 2);
		auto up = this->GetPos().y + (this->GetSize().y / 2);
		auto down = this->GetPos().y - (this->GetSize().y / 2);
		if ((mousePos.x >= left) && (mousePos.x <= right) && (mousePos.y <= up) && (mousePos.y >= down)) {
			return true;
		}
		return false;
	}
	//End class Door

	//Begin class Dimond

	Dimond::Dimond(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform)
		:Entity(pos, size, scale, transform), m_shader("C:/dev/Scar/PFE/src/shaders/VertexShader.sh", "C:/dev/Scar/PFE/src/shaders/FragmentShader.sh")
	{
		m_type = DIMOND; 
	}

	void Dimond::Update() {
		if (this->IsSelected()) {
			m_pos = glm::vec2{ Scar::Event::MouseEvent::GetNormalizedX(),Scar::Event::MouseEvent::GetNormalizedY() };
		}
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();

		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.x * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_transform = glm::rotate(m_transform, glm::radians(m_rot), { 0,0,1 });
		
		m_size = { m_scale.x * m_size.x * (ST / WindowSize.x) ,m_scale.y * m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		m_shader.UnBind();
	}
	void Dimond::Render() {
		if (m_texture != nullptr) {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArrayTextured(m_vertexArray, &m_shader, m_texture));
		}
		else {
			ENGINE()->GetRenderManager()->Push(new Scar::graphics::RenderVertexArray(m_vertexArray, &m_shader));
		}
	}

	bool Dimond::ClickCollision() {
		auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
		auto right = this->GetPos().x + (this->GetSize().x / 2);
		auto left = this->GetPos().x - (this->GetSize().x / 2);
		auto up = this->GetPos().y + (this->GetSize().y / 2);
		auto down = this->GetPos().y - (this->GetSize().y / 2);
		if ((mousePos.x >= left) && (mousePos.x <= right) && (mousePos.y <= up) && (mousePos.y >= down)) {
			auto tmp = mousePos.x - this->GetPos().x;
			if (tmp >= 0) {
				if ((mousePos.y <= up - tmp) && (mousePos.y >= down + tmp)) {
					return true;
				}
			}
			else {
				if ((mousePos.y <= up + tmp) && (mousePos.y >= down - tmp)) {
					return true;
				}
			}
		}
		return false;
	}

	const char* Dimond::Info() {
		return "Dimond";
	}

	Dimond::~Dimond() {

	}
	//End class Dimond

	//Begin class Line
	Line::Line(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& scale, const glm::mat4& transform)
		:Entity(pos,size,scale,transform),m_shader("C:/dev/Scar/PFE/src/shaders/VertexShader.sh", "C:/dev/Scar/PFE/src/shaders/FragmentShader.sh")
	{
		m_type = LINE;
	}	
	Line::~Line() {

	}

	void Line::Render() {
		ENGINE()->GetRenderManager()->Push(new RenderLine(m_vertexArray, &m_shader));
	}

	void Line::Update() {
		m_transform = glm::mat4{ 1.0f };
		static glm::vec2 entitySize = m_size;
		m_size = entitySize;
		auto ST = ENGINE()->GetWindow()->GetSizeTheoric();
		auto WindowSize = ENGINE()->GetWindow()->GetWindowSize();

		m_transform = glm::translate(m_transform, glm::vec3{ m_pos.x,m_pos.y,0.0f });
		m_transform = glm::scale(m_transform, glm::vec3{ m_scale.y * (ST / WindowSize.x),m_scale.y * (ST / WindowSize.y),0.0f });
		m_transform = glm::rotate(m_transform, glm::radians(m_rot), { 0,0,1 });

		m_size = { m_scale.y * m_size.y * (ST / WindowSize.x) ,m_scale.y * m_size.y * (ST / WindowSize.y) };
		m_shader.Bind();
		m_shader.SetMat4("model", m_transform);
		m_shader.SetVec4("Color", m_color);
		
		m_shader.UnBind();
	}

	bool Line::ClickCollision() {
		//todo
		return false;
	}

	const char* Line::Info() {
		return "Line";
	}


}