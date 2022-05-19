#pragma once
#include <memory>
#include "core/core.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/FrameBuffer.h"

namespace Scar::graphics {
	/*
	class Shader;
	class Mesh;
	class FrameBuffer

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
}