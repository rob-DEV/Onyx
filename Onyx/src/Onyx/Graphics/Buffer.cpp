#include "onyxpch.h"
#include "Buffer.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Onyx {



	Onyx::VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexBuffer(vertices, size);

		return nullptr;

	}

	Onyx::IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLIndexBuffer(indices, size);

		return nullptr;

	}

}