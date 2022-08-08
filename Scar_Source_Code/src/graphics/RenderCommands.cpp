#include "graphics/RenderCommands.h"
#include "glad/glad.h"
#include "core/Log.h"
#include "graphics/Helpers.h"
#include "graphics/Shader.h"
#include "core/Engine.h"
namespace Scar::graphics {
	RenderVertexArray::RenderVertexArray(VertexArray* va, Shader* shader)
		:m_vertexArray(va),m_shader(shader)
	{	

	}
	
	void RenderVertexArray::Execute()
	{
		if (m_vertexArray && m_shader) {
			if (m_vertexArray->IsUploaded()) {
				m_vertexArray->Bind();
				m_shader->Bind();
				GlCall(glDrawElements(GL_TRIANGLES, m_vertexArray->GetElementCount(), GL_UNSIGNED_INT, (void*)0));
				m_vertexArray->UnBind();
				m_shader->UnBind();
			}
			else {
				SCAR_WARN("RenderVertexArray::Execute() Vertex array is not uploaded - VertexArray::Upload()");
			}
		}
		else {
			SCAR_ERROR("RenderVertexArray::Execute() Attemting to execute RenderMesh with invalid data ");
		}
	}

	RenderLine::RenderLine(VertexArray* va, Shader* shader)
		:RenderVertexArray(va,shader)
	{

	}

	void RenderLine::Execute() {
		if (m_vertexArray && m_shader) {
			if (m_vertexArray->IsUploaded()) {
				m_vertexArray->Bind();
				m_shader->Bind();
				GlCall(glDrawArrays(GL_LINES, 0, 2));
				m_vertexArray->UnBind();
				m_shader->UnBind();
			}
			else {
				SCAR_WARN("RenderVertexArray::Execute() Vertex array is not uploaded - VertexArray::Upload()");
			}
		}
		else {
			SCAR_ERROR("RenderVertexArray::Execute() Attemting to execute RenderMesh with invalid data ");
		}
	}

	RenderVertexArrayTextured::RenderVertexArrayTextured(VertexArray* va, Shader* shader, Texture* texture)
		:RenderVertexArray(va,shader)
	{
		m_vertexArray = va;
		m_shader = shader; 
		m_texture = texture;
	}
	void RenderVertexArrayTextured::Execute()  {
		if (m_vertexArray && m_shader && m_texture ) {
			if (m_vertexArray->IsUploaded()) {
				m_shader->Bind();
				m_texture->Bind();
				m_vertexArray->Bind();

				GlCall(glDrawElements(GL_TRIANGLES, m_vertexArray->GetElementCount(), GL_UNSIGNED_INT, (void*)0));
				m_vertexArray->UnBind();
				m_shader->UnBind();
				m_texture->UnBind();
			}
			else {
				SCAR_WARN("RenderVertexArrayTextured::Execute() Vertex buffer is not uploaded - call VertexArray::Upload()");
			}
		}
		else {
			SCAR_ERROR("RenderVertexArrayTextured::Execute() Attemting to execute RenderVertexArray with invalid data ");
		}
	}

	void PushFrameBuffer::Execute() {
		if (m_framebuffer != nullptr) {
			ENGINE()->GetRenderManager()->PushFrameBuffer(m_framebuffer);
		}
	}

	void PopFrameBuffer::Execute() {
		if (m_framebuffer != nullptr) {
			ENGINE()->GetRenderManager()->PopFrameBuffer();
		}
	}
}