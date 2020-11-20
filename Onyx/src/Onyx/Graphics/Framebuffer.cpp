#include "onyxpch.h"
#include "Framebuffer.h"

#include <Onyx/Graphics/RendererAPI.h>
#include <Platform/OpenGL/OpenGLFramebuffer.h>

namespace Onyx {

	Framebuffer* Framebuffer::Create(const FramebufferSpecification& specification)
	{

		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			return new OpenGLFramebuffer(specification);

		return nullptr;

	}

}