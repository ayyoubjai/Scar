#include "graphics/RenderCommands.h"
#include "glad/glad.h"
#include "core/Log.h"
#include "graphics/Helpers.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
<<<<<<< HEAD
#include "core/Engine.h"
namespace Scar::graphics {
	RenderMesh::RenderMesh(Mesh* mesh, Shader* shader)
		:m_mesh(mesh),m_shader(shader)
=======
namespace Scar::graphics {
	RenderMesh::RenderMesh(Mesh* mesh, Shader* shader):m_mesh(mesh),m_shader(shader)
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
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
<<<<<<< HEAD
	RenderTexture::RenderTexture(Mesh* mesh, Shader* shader, Texture* texture)
		:RenderMesh(mesh,shader)
	{
		m_mesh = mesh; 
		m_shader = shader; 
		m_texture = texture;
	}
	void RenderTexture::Execute()  {
		if (m_mesh && m_shader) {
			m_shader->Bind();
			m_texture->Bind();
			m_mesh->Bind();
			
			GlCall(glDrawElements(GL_TRIANGLES, m_mesh->GetElementCount(), GL_UNSIGNED_INT, (void*)0));
			m_mesh->UnBind();
			m_shader->UnBind();
			m_texture->UnBind();
		}
		else {
			SCAR_ERROR("Attemting to execute RenderMesh with invalid data ");
		}
	}

	void PushFrameBuffer::Execute() {
		if (m_framebuffer != nullptr) {
			ENGINE()->GetRenderManager()->PushFrameBuffer(m_framebuffer);
		}
		else {
			SCAR_ERROR("Framebuffer is empty");
		}
	}

	void PopFrameBuffer::Execute() {
		if (m_framebuffer != nullptr) {
			ENGINE()->GetRenderManager()->PopFrameBuffer();
		}
		else {
			SCAR_ERROR("Framebuffer stack is empty");
		}
	}
=======

>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
}