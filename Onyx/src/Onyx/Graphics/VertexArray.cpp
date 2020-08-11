#include "onyxpch.h"
#include "VertexArray.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Onyx {

	Onyx::VertexArray* VertexArray::Create()
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexArray();

		return nullptr;
	}

}