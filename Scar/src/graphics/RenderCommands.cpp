#include "graphics/RenderCommands.h"
#include "glad/glad.h"
#include "core/Log.h"
#include "graphics/Helpers.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
namespace Scar::graphics {
	RenderMesh::RenderMesh(Mesh* mesh, Shader* shader):m_mesh(mesh),m_shader(shader)
	{	

	}
	
	void RenderMesh::Execute()
	{
		if (m_mesh && m_shader) {
			m_mesh->Bind();
			m_shader->Bind();
			GlCall(glDrawElements(GL_TRIANGLES, m_mesh->GetElementCount(), GL_UNSIGNED_INT, (void*)0));
			m_mesh->UnBind();
			m_shader->UnBind();
		}
		else {
			SCAR_ERROR("Attemting to execute RenderMesh with invalid data ");
		}
	}

}