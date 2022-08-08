#include "managers/RenderManager.h"
#include "glad/glad.h"
#include "core/Log.h"
#include "graphics/Helpers.h"
#include "core/Engine.h"
namespace Scar::Managers {
	void RenderManager::Initialize()
	{
		SCAR_INFO("OpenGl \n\tVendor : {}\n\tRenderer : {}\n\tVersion : {}", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION));
		//open gl shit
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//SetClearColor(0, 0, 1, 0);
	}

	void RenderManager::ShutDown()
	{
		while (m_rendercommands.size() > 0) {
			m_rendercommands.pop();
		}
	}

	void RenderManager::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	
	void RenderManager::Push(Scar::graphics::RenderCommands* rc)
	{
		m_rendercommands.push(rc);
	}
	
	void RenderManager::Execute()
	{
		while (m_rendercommands.size() > 0) {
			graphics::RenderCommands* rc = m_rendercommands.front();
			m_rendercommands.pop();
			rc->Execute();
		}
	}

	void RenderManager::Clear() {
		SCAR_ASSERT(m_rendercommands.size() == 0, "Unflushed render commands frome previous frame");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderManager::SetWireframeMode(bool enabled) {
		if (enabled) {
			GlCall(glPolygonMode(GL_FRONT_AND_BACK,GL_LINE));
		}
		else {
			GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
	}
	void RenderManager::PushFrameBuffer(graphics::FrameBuffer* framebuffer)
	{
		//m_framebuffers.push(framebuffer);
		framebuffer->Bind();
		int w, h;
		framebuffer->GetFrameBufferSize(w, h);
		SetViewport(0,0,w,h);
		float r, g, b, a;
		framebuffer->GetClearColor(r, g, b, a);
		SetClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void RenderManager::PopFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		int w, h;
		ENGINE()->GetWindow()->GetWindowSize(w, h);
		SetViewport(0, 0, w, h);
	}

	void RenderManager::SetViewport(int x, int y, unsigned int width, unsigned int height) {
		glViewport(x,y,width,height);
	}
}