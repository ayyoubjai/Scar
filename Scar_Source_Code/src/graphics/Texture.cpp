#include "graphics/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb/stb_image.h"
#include "glad/glad.h"
#include "core/Log.h"
#include "graphics/Helpers.h"
namespace Scar::graphics {
	Texture::Texture()
		:m_path(nullptr), m_binded(false), m_textunit(GL_TEXTURE0) 
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		/*
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		*/
	}

	Texture::Texture(const char* path )
		:m_path(path),m_binded(false),m_textunit(GL_TEXTURE0) 
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		stbi_set_flip_vertically_on_load(0);

		unsigned char* data = stbi_load(m_path, &m_width, &m_height, &m_nbrchannels, 0);
		GLenum TextureFormat = 0;
		if (m_nbrchannels == 3) {
			TextureFormat = GL_RGB;
		}
		else if (m_nbrchannels == 4) {
			TextureFormat = GL_RGBA;
		}
		else {
			SCAR_ERROR("Unsuported Texture format number of channels :{}", m_nbrchannels);
		}

		if (data && TextureFormat != 0) {
			GlCall(glTexImage2D(GL_TEXTURE_2D, 0, TextureFormat, m_width, m_height, 0, TextureFormat, GL_UNSIGNED_BYTE, data));
			glGenerateMipmap(GL_TEXTURE_2D);
			
		}
		else {
			SCAR_ERROR("failed to load the texture");
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	Texture::~Texture() {

	}
	void Texture::Bind()
	{
		SCAR_ASSERT(!m_binded, "Attmpting to bind Texture twice ");
		glActiveTexture(m_textunit);
		glBindTexture(GL_TEXTURE_2D, ID);
		m_binded = true;
	}
	void Texture::UnBind()
	{
		SCAR_ASSERT(m_binded, "Attempting to unbind Texture twice ");
		glBindTexture(GL_TEXTURE_2D, 0);
		m_binded = false;
	}

	void Texture::ActiveTextUnit(GLenum textunit) 
	{
		m_textunit = textunit;
	}
}