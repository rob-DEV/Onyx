#include "onyxpch.h"
#include "Renderer3D.h"

#include <Onyx/Graphics/RendererAPI.h>
#include <Platform/OpenGL/OpenGLRenderer3D.h>

namespace Onyx {

	Renderer3D* Renderer3D::s_Instance = nullptr;

	void Renderer3D::Init() {

		//SELECT RENDERER2D based on which RENDERER API is in use
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			s_Instance = new OpenGLRenderer3D();

		//if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
		//	s_Instance = new VulkanRenderer2D();

		s_Instance->InitImplementation();

	}

}