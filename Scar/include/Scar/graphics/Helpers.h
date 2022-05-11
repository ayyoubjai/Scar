#pragma once
#include "glad/glad.h"
#include "core/Log.h"
namespace Scar {
	static void GlClearError() {
		while (glGetError()!=GL_NO_ERROR);
	}

	static bool GlLogCall() {
		while (GLenum error=glGetError()) {
			SCAR_ERROR("[OpenGl ERROR] : {}", error);
			return false;
		}
		return true;
	}

}

#define GlCall(x) Scar::GlClearError();\
x;\
SCAR_ASSERT(Scar::GlLogCall(),"");