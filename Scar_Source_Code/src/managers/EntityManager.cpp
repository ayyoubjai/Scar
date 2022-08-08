#include "managers/EntityManager.h"
#include "events/MouseEvent.h"
#include "core/Engine.h"
#include "core/Log.h"
#include <mutex>
namespace Scar::Managers {
	unsigned int EntityManager::s_entitiesCount = 0;

	EntityManager::EntityManager() 
		:m_entitySelected(nullptr),m_hold(0)
	{
		
	}

	EntityManager::~EntityManager()
	{
		delete m_entitySelected;
		m_entitySelected = nullptr;
	}

	EntityManager* EntityManager::Get() {
		static std::mutex s_mutex;
		static EntityManager* s_instance = nullptr;
		std::lock_guard<std::mutex> lock(s_mutex);
		return (s_instance == nullptr) ? s_instance = new EntityManager() : s_instance;
	}

	void EntityManager::AddEntity(graphics::Entity* entity) {
		
		entity->SetID(s_entitiesCount);
		s_entitiesCount++;
		m_entities.push_back(entity);
	}

	void EntityManager::DeleteEntity(graphics::Entity* entity) {
		std::vector<graphics::Entity*>::iterator iter;
		for (iter = m_entities.begin(); iter != m_entities.end(); ++iter) {
			if (entity == (*iter)) {
				m_entities.erase(iter);
			}
		}
	}

	void EntityManager::DeleteEntity(int entityID) {
		std::vector<graphics::Entity*>::iterator iter;
		for (iter = m_entities.begin(); iter != m_entities.end(); ++iter) {
			if (entityID == (*iter)->GetID()) {
				m_entities.erase(iter);
				s_entitiesCount--;
				break;
			}
		}
		int i = 0;
		for (iter = m_entities.begin(); iter != m_entities.end(); ++iter) {
			(*iter)->SetID(i);
			i++;
		}
	}
	/*
	void EntityManager::UpdateEntitiesID() {
		std::vector<graphics::Entity*>::iterator iter;
		int i = 0;
		for (iter = m_entities.begin(); iter != m_entities.end(); ++iter) {
			(*iter)->SetID(i);
			i++;
		}
	}
	*/
	void EntityManager::AddSquareFilled(graphics::VertexArray* va) {
		graphics::Entity* entity = new graphics::SquareFilled(glm::vec2{ 0.0f,0.0f }, { 0.5f,0.5f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		AddEntity(entity);
	}

	void EntityManager::AddDisk(graphics::VertexArray* va) {
		graphics::Entity* entity = new graphics::Disk(glm::vec2{ 0.0f ,0.0f }, { 0.5f,0.5f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		AddEntity(entity);
	}

	void EntityManager::AddTriangle(graphics::VertexArray* va) {
		graphics::Entity* entity = new graphics::Triangle(glm::vec2{ 0.0f ,0.0f }, { 0.5f,0.5f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		AddEntity(entity);
	}

	void EntityManager::AddSquare(graphics::VertexArray* va, graphics::Texture* texture) {
		graphics::Entity* entity = new graphics::Square(glm::vec2{ 0.0f ,0.0f }, { 0.5f,0.5f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		entity->SetTexture(texture);
		AddEntity(entity);
	}

	void EntityManager::AddIcon(graphics::Entity::EntityType type,graphics::VertexArray* va, graphics::Texture* texture) {
		graphics::Entity* entity = new graphics::Icon(type,glm::vec2{ 0.0f ,0.0f }, { 0.15f,0.20f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		entity->SetTexture(texture);
		AddEntity(entity);
	}

	void EntityManager::AddDimond(graphics::VertexArray* va) {
		graphics::Entity* entity = new graphics::Dimond(glm::vec2{ 0.0f ,0.0f }, { 0.5f,0.5f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		AddEntity(entity);
	}

	void EntityManager::AddLine(graphics::VertexArray* va) {
		graphics::Entity* entity = new graphics::Line(glm::vec2{ 0.0f ,0.0f }, { 0.5f,0.5f }, { 1.0,1.0 });
		entity->SetVertexArray(va);
		AddEntity(entity);
	}

	void EntityManager::ClearEntities() {
		
		/*
		for (int i = 0;i<m_entities.size();i++) {
			SCAR_DEBUG("delete Entity : {}",i);
			m_entities.pop_back();
			
		}
		*/
		int i = 0;
		for (graphics::Entity* entity : m_entities) {
			SCAR_DEBUG("delete Entity : {}", i);
			delete entity;
			i++;
		}
		m_entities.clear();
		s_entitiesCount = 0;
		
	}

	void EntityManager::Update() {
		//SCAR_WARN("you are inside the entitymgr Update");
		std::vector<graphics::Entity*>::reverse_iterator iter;
		bool event = Event::MouseEvent::ButtonDown(SCAR_EVENT_MOUSE_LEFT);
		for (iter = m_entities.rbegin(); iter != m_entities.rend(); iter++) {
			auto& entity = *iter;
			if (event) {
				if (m_hold == 0) {
					/*
					auto mousePos = glm::vec2{ Event::MouseEvent::GetNormalizedX(),Event::MouseEvent::GetNormalizedY() };
					auto right = entity->GetPos().x + (entity->GetSize().x / 2);
					auto left = entity->GetPos().x - (entity->GetSize().x / 2);
					auto up = entity->GetPos().y + (entity->GetSize().y / 2);
					auto down = entity->GetPos().y - (entity->GetSize().y / 2);
					if ((mousePos.x >= left) && (mousePos.x <= right) && (mousePos.y <= up) && (mousePos.y >= down)) {*/
					if(entity->ClickCollision()){
						//SCAR_WARN("you selected an entity ID({})",entity->GetID());
						m_entitySelected = entity;
						m_hold++;
						break;
					}
					
				}
				if (m_hold == 2) {
					m_entitySelected = nullptr;
					m_hold = 0;
					break;
				}
			}
			
			entity->Update();
		}
		if (m_hold==1) {
			std::vector<graphics::Entity*> temp;
			for (int i = 0; i < m_entities.size(); i++) {
				if (!m_entities[i]->IsSelected()) {
					temp.push_back(m_entities[i]);
				}
			}
			temp.push_back(m_entitySelected);
			m_entities.clear();
			m_entities = temp;
			m_hold++;
		}
		//SCAR_WARN("hold = {}", m_hold);
		
	}

	void EntityManager::Render() {
		for (std::vector<graphics::Entity*>::iterator iter=m_entities.begin();iter!=m_entities.end();iter++) {
			auto& entity = *iter;
			if(!entity->IsSelected())
				entity->Render();
		}
		
		if (m_entitySelected) {
			m_entitySelected->Render();
		}
		
		ENGINE()->GetRenderManager()->Execute();
	}

	graphics::Entity* EntityManager::GetEntity(int id) {
		for (std::vector<graphics::Entity*>::const_iterator iter = m_entities.begin(); iter != m_entities.end(); iter++) {
			if (id == (*iter)->GetID()) {
				return (*iter);
			}
		}
		return nullptr;
	}
}