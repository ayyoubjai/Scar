#pragma once
#include "core/core.h"
#include "vendor/stb/stb_image.h"
#include <string>
namespace Scar::graphics {
	typedef unsigned int GLenum;

	class SCAR_API Texture {
		unsigned int ID;
		const char* m_path;
		int m_width, m_height;
		int m_nbrchannels;//this could be 3 for RGB or 4 for RGBA
		bool m_binded;
		GLenum m_textunit;

	public:
		Texture();
		Texture(const char* path);
		~Texture();
		void ActiveTextUnit(GLenum textunit);
		void Bind();
		void UnBind();

		inline unsigned int GetID() const { return ID; }
	};
}