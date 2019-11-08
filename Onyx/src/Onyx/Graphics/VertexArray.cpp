#include "onyxpch.h"
#include "VertexArray.h"

#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Onyx {

	Onyx::VertexArray* VertexArray::create()
	{
		std::string API = "OpenGL";

		if (API == "OpenGL")
			return new OpenGLVertexArray();

		return nullptr;
	}

}