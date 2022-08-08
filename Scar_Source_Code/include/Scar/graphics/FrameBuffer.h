#pragma once
#include "core/core.h"

namespace Scar::graphics {
	class SCAR_API FrameBuffer {
		unsigned int ID;
		unsigned int m_textid;
		unsigned int m_renderid;
		unsigned int m_width;
		unsigned int m_height;
		float m_ccr, m_ccg, m_ccb, m_cca;
	public:
		inline void SetClearColor(float ccr, float ccg, float ccb, float cca) {
			m_ccr = ccr;
			m_ccg = ccg;
			m_ccb = ccb;
			m_cca = cca;
		}
		
		inline unsigned int GetFBO() {
			return ID;
		}

		inline unsigned int GetRenderBuffer() {
			return m_renderid;
		}

		inline unsigned int GetTexture() {
			return m_textid;
		}

		inline void GetClearColor(float& r, float& g, float& b, float& a) {
			r = m_ccr;
			g = m_ccg;
			b = m_ccb;
			a = m_cca;
		}

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
		inline void SetWidth(int width)  { m_width=width; }
		inline void SetHeight(int height)  { m_height=height; }

		void Bind();
		void UnBind();
		FrameBuffer(unsigned int width,unsigned int height);
		~FrameBuffer();
		void GetFrameBufferSize(int& width,int& height);
	};
}