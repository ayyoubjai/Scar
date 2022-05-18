#pragma once
#include <memory>
#include "core/core.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
<<<<<<< HEAD
#include "graphics/Texture.h"
#include "graphics/FrameBuffer.h"
=======

>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
namespace Scar::graphics {
	/*
	class Shader;
	class Mesh;
<<<<<<< HEAD
	class FrameBuffer
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
	*/
	class RenderCommands {
	public:
		virtual void Execute() = 0;
		virtual ~RenderCommands() {}
	};

	class SCAR_API RenderMesh :public RenderCommands {
		Shader* m_shader;
		Mesh* m_mesh;
	public:
		RenderMesh(Mesh* mesh, Shader* shader);
		virtual void Execute();
	};
<<<<<<< HEAD

	class SCAR_API RenderTexture :public RenderMesh {
		Shader* m_shader;
		Mesh* m_mesh;
		Texture* m_texture;
	public:
		RenderTexture(Mesh* mesh, Shader* shader,Texture* texture);
		virtual void Execute();
	};

	class SCAR_API PushFrameBuffer :public RenderCommands {
		FrameBuffer* m_framebuffer;
	public:
		PushFrameBuffer(FrameBuffer* framebuffer)
			:m_framebuffer(framebuffer)
		{

		}
		virtual void Execute();
	};

	class SCAR_API PopFrameBuffer :public RenderCommands {
		FrameBuffer* m_framebuffer;
	public:
		PopFrameBuffer(FrameBuffer* framebuffer)
			:m_framebuffer(framebuffer)
		{

		}
		virtual void Execute();
	};
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
}