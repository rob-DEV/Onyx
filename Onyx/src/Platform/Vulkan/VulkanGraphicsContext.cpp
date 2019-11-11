#include "onyxpch.h"
#include "VulkanGraphicsContext.h"

#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32


#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "vulkan/vulkan_win32.h"

namespace Onyx {



	VulkanGraphicsContext::VulkanGraphicsContext(GLFWwindow* window)
	{	
		m_WindowHandle = window;
	}

	VulkanGraphicsContext::~VulkanGraphicsContext()
	{
		delete m_VulkanInstance;
	}

	void VulkanGraphicsContext::init()
	{
		std::cout << "Vulkan Context Initialization\n";

		//initialize Vulkan instance
		m_VulkanInstance = new VulkanInstance(m_WindowHandle);
		//m_VulkanInstance->init();

		
		

		std::cout << "Vulkan Initialization End!\n";
	}

	void VulkanGraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}

