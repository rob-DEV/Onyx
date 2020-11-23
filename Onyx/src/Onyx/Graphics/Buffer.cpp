#include "onyxpch.h"
#include "Buffer.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Onyx {

	VertexBuffer* VertexBuffer::Create()
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexBuffer();

		return nullptr;
	}
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLVertexBuffer(vertices, size);

		return nullptr;

	}

	IndexBuffer* IndexBuffer::Create(uint32_t count)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLIndexBuffer(count);

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLIndexBuffer(indices, count);

		return nullptr;

	}

}