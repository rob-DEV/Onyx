#include "onyxpch.h"
#include "Renderer2D.h"

#include <Onyx/Graphics/RendererAPI.h>
#include <Platform/OpenGL/OpenGLRenderer2D.h>
#include <Platform/Vulkan/VulkanRenderer2D.h>

namespace Onyx {

	Renderer2D* Renderer2D::s_Instance = nullptr;

	void Renderer2D::Init() {

		//SELECT RENDERER2D based on which RENDERER API is in use
		if (RendererAPI::GetAPI() == RendererAPI::API::OpenGL)
			s_Instance = new OpenGLRenderer2D();

		//if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan)
			//s_Instance = new VulkanRenderer2D();

		s_Instance->InitImplementation();

	}

}