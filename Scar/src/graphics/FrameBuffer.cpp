#include "graphics/FrameBuffer.h"
#include "graphics/Helpers.h"
#include "glad/glad.h"

namespace Scar::graphics {
	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ID);
	}
	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
		:ID(0),m_textid(0),m_renderid(0), m_width(width), m_height(height),m_ccr(0),m_ccg(0),m_ccb(1),m_cca(1)
	{
		GlCall(glGenFramebuffers(1, &ID));
		GlCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));

		GlCall(glGenTextures(1, &m_textid));
		GlCall(glBindTexture(GL_TEXTURE_2D, m_textid));
		
		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,GL_UNSIGNED_BYTE,nullptr));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GlCall(glBindTexture(GL_TEXTURE_2D, 0));
		GlCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textid, 0));

		GlCall(glGenRenderbuffers(1, &m_renderid));
		GlCall(glBindRenderbuffer(GL_RENDERBUFFER, m_renderid));
		GlCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height));
		GlCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderid));

		//checking for the framebuffer status
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			SCAR_ERROR("Fail to create framebuffer");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	
	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &ID);
		m_textid = 0;
		m_renderid = 0;
		m_width = 0;
		m_height = 0;

	}

	void FrameBuffer::GetFrameBufferSize(int& width,int& height) {
		width = m_width;
		height = m_height;
	}

}