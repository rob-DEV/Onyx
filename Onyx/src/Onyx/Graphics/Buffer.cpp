#include "onyxpch.h"
#include "Buffer.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Onyx {

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexBuffer(vertices, size);

		return nullptr;

	}

	VertexBuffer* VertexBuffer::create(uint32_t size)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexBuffer(size);

		return nullptr;
	}


	IndexBuffer* IndexBuffer::create(uint32_t count)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLIndexBuffer(count);

		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		if (RendererAPI::getAPI() == RendererAPI::API::OpenGL)
			return new OpenGLIndexBuffer(indices, count);

		return nullptr;

	}

}