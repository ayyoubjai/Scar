#include "core/Engine.h"
#include "core/EntryPoint.h"
#include "graphics/Entity.h"
#include "managers/EntityManager.h"
#include "application/Application.h"
#include "window/Window.h"
#include "events/KeyEvent.h"
#include <fstream>
#include <string>
using namespace Scar;

class pfe :public Scar::Application {
	graphics::VertexArray* m_va,*m_vaSquare,*m_vaTriangle,*m_vaIcon,*m_vaDimond,*m_vaLine;
	graphics::Texture* m_squareFilled,*m_whiteSquare,*m_greenSquare,*m_disk,*m_triangle,*m_close,*m_door,*m_greenDoor,*m_dimond,*m_line,*m_closeBlack,*m_download,
		*m_upload,*m_desk,*m_sink,*m_toilet,*m_car,*m_stove,*m_sofa,*m_chair,*m_roundTable,*m_diningTable,*m_bed;
	unsigned int m_screenW, m_screenH;
	int m_delete = 0;
	ImVec2 m_buttonSize = { 17.f,17.f };

public:
	void Initialize() override {
		
		//Upload the icons
		m_bed = new graphics::Texture("c:/dev/Scar/PFE/assets/bed.png");
		m_roundTable = new graphics::Texture("c:/dev/Scar/PFE/assets/round-table.png");
		m_diningTable = new graphics::Texture("c:/dev/Scar/PFE/assets/dining-table.png");
		m_chair = new graphics::Texture("c:/dev/Scar/PFE/assets/chair.png");
		m_car = new graphics::Texture("C:/dev/Scar/PFE/assets/car.png");
		m_stove = new graphics::Texture("C:/dev/Scar/PFE/assets/stove.png");
		m_sofa = new graphics::Texture("C:/dev/Scar/PFE/assets/sofa.png");
		m_sink = new graphics::Texture("C:/dev/Scar/PFE/assets/sink.png");
		m_toilet = new graphics::Texture("C:/dev/Scar/PFE/assets/toilet.png");
		m_desk = new graphics::Texture("C:/dev/Scar/PFE/assets/desk.png");
		m_close = new graphics::Texture("C:/dev/Scar/PFE/assets/close-window.png");
		m_greenSquare = new graphics::Texture("C:/dev/Scar/PFE/assets/green-square64.png");
		m_whiteSquare = new graphics::Texture("C:/dev/Scar/PFE/assets/white-square64.png");
		m_triangle = new graphics::Texture("C:/dev/Scar/PFE/assets/triangle40.png");
		m_squareFilled = new graphics::Texture("C:/dev/Scar/PFE/assets/square-full.png");
		m_disk = new graphics::Texture("C:/dev/Scar/PFE/assets/disk.png");
		m_greenDoor = new graphics::Texture("C:/dev/Scar/PFE/assets/green-door.png");
		m_door = new graphics::Texture("C:/dev/Scar/PFE/assets/door.png");
		m_dimond = new graphics::Texture("C:/dev/Scar/PFE/assets/dimond.png");
		m_line = new graphics::Texture("C:/dev/Scar/PFE/assets/vertical-line.png");
		m_closeBlack = new graphics::Texture("C:/dev/Scar/PFE/assets/close.png");
		m_download = new graphics::Texture("C:/dev/Scar/PFE/assets/save.png");
		m_upload = new graphics::Texture("C:/dev/Scar/PFE/assets/upload.png");
		//Init vaos
		m_va = new graphics::VertexArray();
		m_vaSquare = new graphics::VertexArray();
		m_vaTriangle = new graphics::VertexArray();
		m_vaIcon = new graphics::VertexArray();
		m_vaDimond = new graphics::VertexArray();
		m_vaLine = new graphics::VertexArray();
		{
			graphics::VertexBuffer<float>* m_vbo = new graphics::VertexBuffer<float>();
			m_vbo->PushVertex({ 0.0f,0.25f,0.0f });
			m_vbo->PushVertex({ 0.0f ,-0.25f,0.0f });
			m_vbo->SetLayout({ 3 });
			m_vbo->Upload();
			m_vaLine->PushBuffer(m_vbo);
		}
		{
			graphics::VertexBuffer<float>* m_vbo = new graphics::VertexBuffer<float>();
			m_vbo->PushVertex({ 0.0f,-0.25f,0.0f });
			m_vbo->PushVertex({ 0.25f ,0.0f,0.0f });
			m_vbo->PushVertex({ 0.0f ,0.25f,0.0f  });
			m_vbo->PushVertex({ -0.25f,0.0f,0.0f  });
			m_vbo->SetLayout({ 3 });
			m_vbo->Upload();
			m_vaDimond->PushBuffer(m_vbo);
		}

		{
			graphics::VertexBuffer<float>* m_vbo = new graphics::VertexBuffer<float>();
			m_vbo->PushVertex({ -0.1f,-0.1f,0.0f });
			m_vbo->PushVertex({ 0.1f ,-0.1f,0.0f });
			m_vbo->PushVertex({ 0.1f ,0.1f,0.0f });
			m_vbo->PushVertex({ -0.1f ,0.1f,0.0f });
			m_vbo->SetLayout({ 3 });
			m_vbo->Upload();
			m_vaIcon->PushBuffer(m_vbo);
		}
		
		{
			graphics::VertexBuffer<float>* m_vbo = new graphics::VertexBuffer<float>();
			m_vbo->PushVertex({ -0.25f,-0.25f,0.0f });
			m_vbo->PushVertex({ 0.25f ,-0.25f,0.0f });
			m_vbo->PushVertex({ 0 ,0.25f,0.0f });
			m_vbo->SetLayout({ 3 });
			m_vbo->Upload();
			m_vaTriangle->PushBuffer(m_vbo);
		}
		{
			graphics::VertexBuffer<float>* m_vbo = new graphics::VertexBuffer<float>();
			m_vbo->PushVertex({-0.25f,-0.25f,0.0f});
			m_vbo->PushVertex({0.25f ,-0.25f,0.0f});
			m_vbo->PushVertex({0.25f ,0.25f,0.0f });
			m_vbo->PushVertex({-0.25f,0.25f,0.0f });
			m_vbo->SetLayout({ 3});
			m_vbo->Upload();
			m_va->PushBuffer(m_vbo);
			m_vaSquare->PushBuffer(m_vbo);
		}
		{
			graphics::VertexBuffer<short>* m_vbo = new graphics::VertexBuffer<short>();
			m_vbo->PushVertex({ 0,0 });
			m_vbo->PushVertex({ 0,1 });
			m_vbo->PushVertex({ 1,1 });
			m_vbo->PushVertex({ 1,0});
			m_vbo->SetLayout({ 2 });
			m_vbo->Upload();
			m_vaSquare->PushBuffer(m_vbo);
			m_vaIcon->PushBuffer(m_vbo);
		}
		m_va->SetElements({ 0,1,2,0,2,3 });
		m_vaSquare->SetElements({ 0,1,2,0,2,3 });
		m_vaTriangle->SetElements({ 0,1,2 });
		m_vaIcon->SetElements({ 0,1,2,0,2,3 });
		m_vaDimond->SetElements({ 0,1,2,0,2,3 });

		m_vaDimond->Upload();
		m_va->Upload();
		m_vaSquare->Upload();
		m_vaTriangle->Upload();
		m_vaIcon->Upload();
		m_vaLine->Upload();
	}

	void Update() override {
		//SCAR_DEBUG("Aspect Ratio : {}", ENGINE()->GetWindow()->GetAspectRatio());
		EntityMgr()->Update();
		if (Event::KeyEvent::KeyDown(SCAR_EVENT_KEY_SCANCODE_LALT)) {
			ENGINE()->GetWindow()->SetRenderScreen(!ENGINE()->GetWindow()->GetRenderScreen());
		}
	}

	void Render() override {
		EntityMgr()->Render();
	}
								
	void UIRender() override {
		bool my_tool_active=true;
		if (!ENGINE()->GetWindow()->GetRenderScreen()) {
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());	
			//ImGui::ShowDemoWindow();
			
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("File")) {
					if (ImGui::MenuItem("New")) {
						DeleteAll();
					}
					if (ImGui::BeginMenu("Save")) {
						static char path1[64] = "";
						ImGui::InputText("Save Design", path1, 64);
						ImGui::SameLine();
						if (ImGui::ImageButton((void*)m_download->GetID(), m_buttonSize)) {
							SaveDesign(path1);
						}

						
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Open")) {
						
						static char path[64] = "";
						ImGui::InputText("Open a Design", path, 64);
						ImGui::SameLine();
						if (ImGui::ImageButton((void*)m_upload->GetID(), m_buttonSize)) {
							UploadDesign(path);
						}
						ImGui::EndMenu();
					}
					if (ImGui::MenuItem("Exit")) {
						ENGINE()->Quit();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("?")) {
					ImGui::Text("ScarEngine version %d.%d", 0, 1);
					ImGui::Text("Scar est un editor graphique sert a faciliter\n la conception des plan 2D .");
					ImGui::EndMenu();
				}
			}
			ImGui::EndMainMenuBar();
			
			if (ImGui::Begin("Editeur")) {
				if (ImGui::IsWindowHovered()) {
					/*
					ImGui::CaptureMouseFromApp(false);
					ImGui::CaptureKeyboardFromApp(false);
					*/
				}
				else {
					ImGui::CaptureMouseFromApp(true);
					ImGui::CaptureKeyboardFromApp(true);
				}
				ImGui::Image((void*)ENGINE()->GetWindow()->GetFrameBuffer()->GetTexture(), { 600,400 }, { 0.0,1.0 }, { 1.0,0.0 });
			}
			ImGui::End();
			if (ImGui::Begin("Entites")) {
				if (EntityMgr()->GetEntities().size() > 0) {
					for (int i = 0; i < EntityMgr()->GetEntities().size(); i++) {
						ImGui::PushID(i);
						ImGui::Separator();
						graphics::Entity* entity = EntityMgr()->GetEntity(i);
						//if (entity) {

						ImGui::Text("Entite ID : %d", i);
						ImGui::Text("Type : %s", entity->Info());

						float pos[] = { entity->GetPos().x,entity->GetPos().y };
						ImGui::DragFloat2("Position", pos, 0.1f);
						//you can t change color for textures
						if (entity->GetType() < 5) {
							glm::vec4 colorEntity = entity->GetColor();
							float color[] = { colorEntity.x,colorEntity.y,colorEntity.z,colorEntity.w };
							ImGui::ColorEdit4("Couleur ", color);
							entity->SetColor(color[0], color[1], color[2], color[3]);
						}
						float scale[2];
						//scale for disks ruin the selection 

						glm::vec2 scaleEntity = entity->GetScale();
						scale[0] = scaleEntity.x;
						scale[1] = scaleEntity.y;
						ImGui::DragFloat2("Taille", scale, 0.1f);

						float rotEntity = entity->GetRotation();
						ImGui::DragFloat("Rotation", &rotEntity, 0.1f);

						entity->SetRotation(rotEntity);
						entity->SetScale(scale[0], scale[1]);
						entity->SetPos(pos[0], pos[1]);
						ImGui::PopID();

					}
				}

				
			}
			ImGui::End();
			if (ImGui::Begin("Panel de Control")) {
				if (ImGui::ImageButton((void*)m_bed->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::BED);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_roundTable->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::ROUND_TABLE);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_diningTable->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::DINING_TABLE);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_sofa->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::SOFA);
				}

				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_chair->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::CHAIR);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_car->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::CAR);
				}

				if (ImGui::ImageButton((void*)m_stove->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::STOVE);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_sink->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::SINK);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_desk->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::DESK);
				}

				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_door->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::DOOR);
				}
				ImGui::SameLine();

				if (ImGui::ImageButton((void*)m_toilet->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::TOILET);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_squareFilled->GetID(), m_buttonSize)) {
					CreateSquareFilled();
				}
				if (ImGui::ImageButton((void*)m_greenSquare->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::SQUARE);
				}

				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_disk->GetID(), m_buttonSize)) {
					CreateDisk();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_triangle->GetID(), m_buttonSize)) {
					CreateTriangle();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_dimond->GetID(), m_buttonSize)) {
					CreateDimond();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_line->GetID(), m_buttonSize)) {
					CreateLine();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_close->GetID(), m_buttonSize)) {
					DeleteAll();
				}

				//ImGui::SameLine();
				ImGui::InputInt("id", &m_delete);
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_closeBlack->GetID(), m_buttonSize)) {
					if (m_delete < 0 || m_delete >= EntityMgr()->GetEntitiesCount())
						SCAR_FATAL("deleted id not valid");
					else {
						if (!EntityMgr()->GetEntities().empty()) {
							SCAR_FATAL("deleted the entity with id {}", m_delete);
							DeleteEntity(m_delete);
						}
					}
				}
				
				auto st = ENGINE()->GetWindow()->GetSizeTheoric();
				ImGui::DragFloat("Echelle", &st, 1.0f);
				ENGINE()->GetWindow()->SetSizeTheoric(st);
				
			}
			ImGui::End();
			/*
			if (ImGui::Begin("Camera Control")) {
				if (ImGui::Button("Create Entity"))
					CreateSquareFilled();
				float camH = m_cam->GetHeight();
				ImGui::DragFloat("Camera Height (Zoom) : ", &camH, 0.1f);
				m_cam->SetHeight(camH);

				float camRot = m_cam->GetRotation();
				ImGui::DragFloat("Camera Rotation : ", &camRot, 1.0f);
				float camPos[] = { m_cam->GetPos().x,m_cam->GetPos().y };
				ImGui::DragFloat2("Camera Pos", camPos, 0.1f);
				m_cam->SetViewMatrix(glm::vec2{ camPos[0],camPos[1] }, camRot);

			}
			ImGui::End();
			*/
		}
		else {
			if (ImGui::Begin("Entities :")) {
				if (EntityMgr()->GetEntities().size() > 0) {
					for (int i = 0; i < EntityMgr()->GetEntities().size(); i++) {
						ImGui::PushID(i);
						ImGui::Separator();
						graphics::Entity* entity = EntityMgr()->GetEntity(i);
						//if (entity) {

						ImGui::Text("Entite ID : %d", i);
						ImGui::Text("Type : %s", entity->Info());

						float pos[] = { entity->GetPos().x,entity->GetPos().y };
						ImGui::DragFloat2("Position", pos, 0.1f);
						//you can t change color for textures
						if (entity->GetType()<5) {
							glm::vec4 colorEntity = entity->GetColor();
							float color[] = { colorEntity.x,colorEntity.y,colorEntity.z,colorEntity.w };
							ImGui::ColorEdit4("Coulor ", color);
							entity->SetColor(color[0], color[1], color[2], color[3]);
						}
						float scale[2];
						//scale for disks ruin the selection 
						
						glm::vec2 scaleEntity = entity->GetScale();
						scale[0] = scaleEntity.x;
						scale[1] = scaleEntity.y;
						ImGui::DragFloat2("Taille", scale, 0.1f);
		
						float rotEntity = entity->GetRotation();
						ImGui::DragFloat("Rotation", &rotEntity, 0.1f);

						entity->SetRotation(rotEntity);
						entity->SetScale(scale[0], scale[1]);
						entity->SetPos(pos[0], pos[1]);
						ImGui::PopID();

					}
				}
			}
			ImGui::End();
			if (ImGui::Begin("Panel de Control :")) {
				if (ImGui::ImageButton((void*)m_bed->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::BED);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_roundTable->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::ROUND_TABLE);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_diningTable->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::DINING_TABLE);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_sofa->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::SOFA);
				}
				
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_chair->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::CHAIR);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_car->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::CAR);
				}
				
				if (ImGui::ImageButton((void*)m_stove->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::STOVE);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_sink->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::SINK);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_desk->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::DESK);
				}

				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_door->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::DOOR);
				}
				ImGui::SameLine();
				
				if (ImGui::ImageButton((void*)m_toilet->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::TOILET);
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_squareFilled->GetID(), m_buttonSize)) {
					CreateSquareFilled();
				}
				if (ImGui::ImageButton((void*)m_greenSquare->GetID(), m_buttonSize)) {
					CreateIcon(graphics::Entity::SQUARE);
				}

				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_disk->GetID(), m_buttonSize)) {
					CreateDisk();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_triangle->GetID(), m_buttonSize)) {
					CreateTriangle();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_dimond->GetID(), m_buttonSize)) {
					CreateDimond();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_line->GetID(), m_buttonSize)) {
					CreateLine();
				}
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_close->GetID(), m_buttonSize)) {
					DeleteAll();
				}

				//ImGui::SameLine();
				ImGui::InputInt("id", &m_delete);
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_closeBlack->GetID(), m_buttonSize)) {
					if (m_delete < 0 || m_delete >= EntityMgr()->GetEntitiesCount())
						SCAR_FATAL("deleted id not valid");
					else {
						if (!EntityMgr()->GetEntities().empty()) {
							SCAR_FATAL("deleted the entity with id {}", m_delete);
							DeleteEntity(m_delete);
						}
					}
				}
				/*
				static char path1[64] = "";
				ImGui::InputText("Save Design", path1, 64);
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_download->GetID(), m_buttonSize)) {
					SaveDesign(path1);
				}

				static char path[64] = "";
				ImGui::InputText("Upload a Design", path, 64);
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_upload->GetID(), m_buttonSize)) {
					UploadDesign(path);
				}*/
				
				auto st = ENGINE()->GetWindow()->GetSizeTheoric() ;
				ImGui::DragFloat("Echelle", &st, 1.0f);
				ENGINE()->GetWindow()->SetSizeTheoric(st);
				
			}
			ImGui::End();
		}
	}

	void ShutDown() override {

	}

	
	void CreateIcon(graphics::Entity::EntityType type) {
		switch (type) {
		case graphics::Entity::SQUARE:{
			EntityMgr()->AddIcon(graphics::Entity::SQUARE, m_vaIcon, m_squareFilled);
			SCAR_DEBUG("add a Square");
			break;
			}
			
		case graphics::Entity::SINK: {
				EntityMgr()->AddIcon(graphics::Entity::SINK, m_vaIcon, m_sink);
				SCAR_DEBUG("add a Sink");
				break;
			}
		case graphics::Entity::TOILET: {
			EntityMgr()->AddIcon(graphics::Entity::TOILET, m_vaIcon, m_toilet);
			SCAR_DEBUG("add a Toilet");
			break;
		}
		case graphics::Entity::SOFA: {
			EntityMgr()->AddIcon(graphics::Entity::SOFA, m_vaIcon, m_sofa);
			SCAR_DEBUG("add a Sofa");
			break;
		}
		case graphics::Entity::DOOR: {
			EntityMgr()->AddIcon(graphics::Entity::DOOR, m_vaIcon, m_door);
			SCAR_DEBUG("add a Door");
			break;
		}
		case graphics::Entity::STOVE: {
			EntityMgr()->AddIcon(graphics::Entity::STOVE, m_vaIcon, m_stove);
			SCAR_DEBUG("add a Stove");
			break;
		}
		case graphics::Entity::DESK: {
			EntityMgr()->AddIcon(graphics::Entity::DESK, m_vaIcon, m_desk);
			SCAR_DEBUG("add a Desk");
			break;
		}
		case graphics::Entity::CAR: {
			EntityMgr()->AddIcon(graphics::Entity::CAR, m_vaIcon, m_car);
			SCAR_DEBUG("add a Car");
			break;
		}
		case graphics::Entity::CHAIR: {
			EntityMgr()->AddIcon(graphics::Entity::CHAIR, m_vaIcon, m_chair);
			SCAR_DEBUG("add a Chair");
			break;
		}
		case graphics::Entity::ROUND_TABLE: {
			EntityMgr()->AddIcon(graphics::Entity::ROUND_TABLE, m_vaIcon, m_roundTable);
			SCAR_DEBUG("add a Round Table");
			break;
		}
		case graphics::Entity::DINING_TABLE: {
			EntityMgr()->AddIcon(graphics::Entity::DINING_TABLE, m_vaIcon, m_diningTable);
			SCAR_DEBUG("add a Dining Table");
			break;
		}
		case graphics::Entity::BED: {
			EntityMgr()->AddIcon(graphics::Entity::BED, m_vaIcon, m_bed);
			SCAR_DEBUG("add a Bed");
			break;
		}
		}
		
	}


	void CreateSquareFilled() {
		EntityMgr()->AddSquareFilled(m_va);
		SCAR_DEBUG("add a square filled");
	}


	void CreateDisk() {
		EntityMgr()->AddDisk(m_va);
		SCAR_DEBUG("add a cercle");
	}

	void CreateTriangle() {
		EntityMgr()->AddTriangle(m_vaTriangle);
		SCAR_DEBUG("add a Triangle");
	}

	void CreateDoor() {
		EntityMgr()->AddIcon(graphics::Entity::DOOR,m_vaIcon,m_door);
		SCAR_DEBUG("add a Door");
	}

	void CreateDimond() {
		EntityMgr()->AddDimond(m_vaDimond);
		SCAR_DEBUG("add a Dimond");
	}

	void DeleteAll() {
		EntityMgr()->ClearEntities();
	}

	void DeleteEntity(int entityID) {
		EntityMgr()->DeleteEntity(entityID);
	}

	void SaveDesign(std::string path = "Design.scar") {
		//creating the design file std::string("Scar/PFE/designs/")+std::string(
		std::string str = std::string("designs/") + path;
		std::ofstream File;
		File.open(str.c_str());
		File << std::to_string(EntityMgr()->GetEntitiesCount()) + "\n";
		auto& entities = EntityMgr()->GetEntities();
		for (std::vector<graphics::Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++) {
			std::string ent = 
				std::to_string((*iter)->GetType()) + "\n" +
				std::to_string((*iter)->GetPos().x) + "\n" +
				std::to_string((*iter)->GetPos().y) + "\n" +
				std::to_string((*iter)->GetColor().x) + "\n" +
				std::to_string((*iter)->GetColor().y) + "\n" +
				std::to_string((*iter)->GetColor().z) + "\n" +
				std::to_string((*iter)->GetColor().w) + "\n" +
				std::to_string((*iter)->GetRotation()) + "\n" +
				std::to_string((*iter)->GetScale().x) +"\n" +
				std::to_string((*iter)->GetScale().y) + "\n";
			
			File << ent;
		}
		File.close();
	}

	void UploadDesign(std::string path = "Design.png") {
		std::ifstream File;
		path = std::string("designs/") + path;
			File.open(path);
			if (File.is_open()) {
				std::string str;
				getline(File, str);
				unsigned int count = std::stoi(str);
				int x, i = 0;
				float f = 0;
				bool first = true;
				while (i<count) {
					if (first) {
						std::string str1;
						getline(File,str1);
						x = std::stoi(str1);
						switch (x) {
						case graphics::Entity::SQUARE_FILLED: {
							EntityMgr()->AddSquareFilled(m_va);
							break;
						}
						case graphics::Entity::SQUARE: {
							EntityMgr()->AddSquare(m_vaSquare, m_whiteSquare);
							break;
						}
						case graphics::Entity::DISK: {
							EntityMgr()->AddDisk(m_va); 
							break;
						}
						case graphics::Entity::TRIANGLE: {
							EntityMgr()->AddTriangle(m_vaTriangle);
							break;
						}
						case graphics::Entity::DIMOND: {
							EntityMgr()->AddDimond(m_vaDimond); 
							break;
						}
						case graphics::Entity::LINE: {
							EntityMgr()->AddLine(m_vaLine);
							break;
						}
						case graphics::Entity::SINK: {
							EntityMgr()->AddIcon(graphics::Entity::SINK, m_vaIcon, m_sink);
							SCAR_DEBUG("add a Sink");
							break;
						}
						case graphics::Entity::TOILET: {
							EntityMgr()->AddIcon(graphics::Entity::TOILET, m_vaIcon, m_toilet);
							SCAR_DEBUG("add a Toilet");
							break;
						}
						case graphics::Entity::SOFA: {
							EntityMgr()->AddIcon(graphics::Entity::SOFA, m_vaIcon, m_sofa);
							SCAR_DEBUG("add a Sofa");
							break;
						}
						case graphics::Entity::DOOR: {
							EntityMgr()->AddIcon(graphics::Entity::DOOR, m_vaIcon, m_door);
							SCAR_DEBUG("add a Door");
							break;
						}
						case graphics::Entity::STOVE: {
							EntityMgr()->AddIcon(graphics::Entity::STOVE, m_vaIcon, m_stove);
							SCAR_DEBUG("add a Stove");
							break;
						}
						case graphics::Entity::DESK: {
							EntityMgr()->AddIcon(graphics::Entity::DESK, m_vaIcon, m_desk);
							SCAR_DEBUG("add a Desk");
							break;
						}
						case graphics::Entity::CAR: {
							EntityMgr()->AddIcon(graphics::Entity::CAR, m_vaIcon, m_car);
							SCAR_DEBUG("add a Car");
							break;
						}
						case graphics::Entity::CHAIR: {
							EntityMgr()->AddIcon(graphics::Entity::CHAIR, m_vaIcon, m_chair);
							SCAR_DEBUG("add a Chair");
							break;
						}
						case graphics::Entity::ROUND_TABLE: {
							EntityMgr()->AddIcon(graphics::Entity::ROUND_TABLE, m_vaIcon, m_roundTable);
							SCAR_DEBUG("add a Round Table");
							break;
						}
						case graphics::Entity::DINING_TABLE: {
							EntityMgr()->AddIcon(graphics::Entity::DINING_TABLE, m_vaIcon, m_diningTable);
							SCAR_DEBUG("add a Dining Table");
							break;
						}
						case graphics::Entity::BED: {
							EntityMgr()->AddIcon(graphics::Entity::BED, m_vaIcon, m_bed);
							SCAR_DEBUG("add a Bed");
							break;
						}
						}
						
						first = false;
					}
					else {
						//loading the pos
						float pos[2];
						for (int j = 0; j < 2; j++) {
							getline(File,str);
							SCAR_DEBUG("str {}", str.c_str());
							pos[j] = std::stof(str);
						}
						EntityMgr()->GetEntities()[i]->SetPos(pos[0], pos[1]);
						//loading the color
						float color[4];
						for (int j = 0; j < 4; j++) {
							getline(File, str);
							f = std::stof(str);
							SCAR_DEBUG("str {}", str.c_str());
							color[j] = f;
						}
						EntityMgr()->GetEntities()[i]->SetColor(color[0], color[1], color[2], color[3]);
						//loading the rotation
						getline(File, str);
						f = std::stof(str);
						EntityMgr()->GetEntities()[i]->SetRotation(f);
						//loading the scale
						float scale[2];
						for (int j = 0; j < 2; j++) {
							getline(File, str);
							SCAR_DEBUG("str {}", str.c_str());
							f = std::stof(str);
							scale[j] = f;
						}
						EntityMgr()->GetEntities()[i]->SetScale(scale[0], scale[1]);
						first = true; 
						i++;
					}
				}
			}
			File.close();
	}

	void CreateLine() {
		EntityMgr()->AddLine(m_vaLine);
	}

	Scar::WindowProperties CreateWindowProperties() {
		Scar::WindowProperties wps;
		wps.title = "Scar";
		wps.iwps.IsViewportsEnabled = true;
		wps.iwps.IsDockingEnabled = true;
		wps.w = 1050;
		wps.h = 650;
		wps.ccr = 47.f / 255;
		wps.ccg = 79.f / 255;
		wps.ccb = 79.f / 255;
		wps.cca = 1.0f;
		m_screenH = wps.h;
		m_screenW = wps.w;
		return wps;
	}


};

Scar::Application* CreateApplication() {
	return new pfe();
}