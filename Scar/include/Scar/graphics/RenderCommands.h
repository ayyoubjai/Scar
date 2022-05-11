#pragma once
#include <memory>
#include "core/core.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"

namespace Scar::graphics {
	/*
	class Shader;
	class Mesh;
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
}