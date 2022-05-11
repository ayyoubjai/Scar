#pragma once
#include "graphics/RenderCommands.h"
#include "core/core.h"

#include <memory>
#include <queue>

namespace Scar::Managers {
	class SCAR_API RenderManager{
		std::queue<graphics::RenderCommands*> m_rendercommands;
	public:
		RenderManager(){}
		~RenderManager(){}
		void Initialize();
		void ShutDown();
		void SetClearColor(float r, float g, float b, float a);
		void Clear();
		void Submit(graphics::RenderCommands* rc);
		void Flush();
		void SetWireframeMode(bool enabled);
	};
}