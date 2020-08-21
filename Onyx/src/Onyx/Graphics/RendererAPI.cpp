#include "onyxpch.h"
#include "RendererAPI.h"

#include <Platform/OpenGL/OpenGLRendererAPI.h>
#include <Platform/Vulkan/VulkanRendererAPI.h>

namespace Onyx {

	//ABSOLUTE GRAPHICS API SETTING
	//USE THIS TO SET ONYX RENDERING API

	//CURRENTLY SUPPORTING
	//OPEN GL
	//VULKAN

	///////////////////////////////////////////////////////////////
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	///////////////////////////////////////////////////////////////
	
	//TURN VSYNC ON OR OFF
	bool RendererAPI::s_Vsync = true;


	RendererAPI* RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None: printf("No API selected\n"); assert(false);
			case RendererAPI::API::OpenGL: return new OpenGLRendererAPI();
			//case RendererAPI::API::Vulkan: return new VulkanRendererAPI();
		}


		printf("Unknown Renderer API\n"); assert(false);
		return nullptr;
	}
	
	
}