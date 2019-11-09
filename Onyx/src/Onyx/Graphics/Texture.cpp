#include "onyxpch.h"
#include "Texture.h"

#include <Platform/OpenGL/OpenGLTexture.h>

namespace Onyx {


	Texture2D* Texture2D::create(const std::string& path) {

		std::string API = "OpenGL";

		if (API == "OpenGL")
			return new OpenGLTexture2D(path);

		return nullptr;


	}


	Onyx::Texture2D* Texture2D::create(uint32_t width, uint32_t height)
	{
		std::string API = "OpenGL";

		if (API == "OpenGL")
			return new OpenGLTexture2D(width, height);

		return nullptr;
	}

}