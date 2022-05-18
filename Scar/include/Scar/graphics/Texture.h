#pragma once
#include "core/core.h"
#include "vendor/stb/stb_image.h"
#include <string>
namespace Scar::graphics {
	typedef unsigned int GLenum;

	class SCAR_API Texture {
		unsigned int ID;
		const char* m_path;
		int m_width, m_height,m_nbrchannels;
		bool m_binded;
		GLenum m_textunit;

	public:
		Texture(const char* path);
		~Texture();
		void ActiveTextUnit(GLenum textunit);
		void Bind();
		void UnBind();
	};
}