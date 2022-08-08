#pragma once
#include "core/core.h"
#include "graphics/Entity.h"
#include <vector>
namespace Scar::Managers {

	class SCAR_API EntityManager{
		static unsigned int s_entitiesCount;
		unsigned int m_screenW, m_screenH;
		std::vector<Scar::graphics::Entity*> m_entities;
		graphics::Entity* m_entitySelected;
		int m_hold;
		EntityManager();
	public:
		~EntityManager();

		static EntityManager* Get();
		
		inline Scar::graphics::Entity* GetEntitySelected() const { return m_entitySelected; }
		inline unsigned int GetEntitiesCount() const { return m_entities.size(); }
		inline std::vector<graphics::Entity*>& GetEntities() { return m_entities; }
		//void ClearEntities();
		

		graphics::Entity* GetEntity(int id) ;
		void Update();
		void Render();
		void AddEntity(Scar::graphics::Entity* entity);
		void AddSquareFilled(graphics::VertexArray* va);
		void AddDisk(graphics::VertexArray* va);
		void AddTriangle(graphics::VertexArray* va);
		void AddSquare(graphics::VertexArray* va,graphics::Texture* texture);
		void AddIcon(graphics::Entity::EntityType type,graphics::VertexArray* va, graphics::Texture* texture);
		
		void AddDimond(graphics::VertexArray* va);
		void AddLine(graphics::VertexArray* va);
		//void UpdateEntitiesID();
		
		void DeleteEntity(int entityID);
		void DeleteEntity(Scar::graphics::Entity* entity);
		void ClearEntities();
	};
}

#define EntityMgr() Scar::Managers::EntityManager::Get()