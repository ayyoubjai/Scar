#pragma once
<<<<<<< HEAD
#include "core/core.h"
#include "graphics/RenderCommands.h"

#include <memory>
#include <queue>
#include <stack>
=======
#include "graphics/RenderCommands.h"
#include "core/core.h"

#include <memory>
#include <queue>
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4

namespace Scar::Managers {
	class SCAR_API RenderManager{
		std::queue<graphics::RenderCommands*> m_rendercommands;
<<<<<<< HEAD
		std::stack<graphics::FrameBuffer*> m_framebuffers;
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
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
<<<<<<< HEAD
		void PushFrameBuffer(graphics::FrameBuffer* framebuffer);
		void PopFrameBuffer();
		void SetViewport(int x, int y, unsigned int width, unsigned int height);
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	};
}