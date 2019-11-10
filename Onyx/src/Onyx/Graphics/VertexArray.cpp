#include "onyxpch.h"
#include "VertexArray.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Onyx {

	Onyx::VertexArray* VertexArray::create()
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexArray();

		return nullptr;
	}

}