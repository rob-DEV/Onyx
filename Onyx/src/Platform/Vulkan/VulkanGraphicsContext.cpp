#include "onyxpch.h"
#include "VulkanGraphicsContext.h"


#include <GLFW/glfw3.h>

namespace Onyx {

	VulkanGraphicsContext::VulkanGraphicsContext(GLFWwindow* window)
	{
		m_WindowHandle = window;
	}

	VulkanGraphicsContext::~VulkanGraphicsContext()
	{
		delete m_VulkanSurface;
		delete m_VulkanInstance;
	}

	void VulkanGraphicsContext::init()
	{
		std::cout << "Vulkan Context Initialization\n";


		//creates and assigns the initial vkInstance 
		m_VulkanInstance = VulkanInstance::create();
		m_VulkanSurface = VulkanSurface::create(m_WindowHandle);


		std::cout << "Vulkan Initialization End!\n";
	}

	void VulkanGraphicsContext::swapBuffers()
	{
		
	}

}

