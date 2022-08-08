#pragma once
#include "core/core.h"
#include "graphics/RenderCommands.h"

#include <memory>
#include <queue>
#include <stack>

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
		void Push(graphics::RenderCommands* rc);
		void Execute();
		void SetWireframeMode(bool enabled);
		void PushFrameBuffer(graphics::FrameBuffer* framebuffer);
		void PopFrameBuffer();
		void SetViewport(int x, int y, unsigned int width, unsigned int height);
	};
}