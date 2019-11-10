#include "onyxpch.h"
#include "VulkanGraphicsContext.h"


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Onyx {



	VulkanGraphicsContext::VulkanGraphicsContext(GLFWwindow* window)
	{	
		m_WindowHandle = window;
		m_VulkanInstance = NULL;
	}

	void VulkanGraphicsContext::init()
	{
		std::cout << "Vulkan Init\n";

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::cout << extensionCount << " extensions supported" << std::endl;
		m_VulkanInstance = new VulkanInstance();


	}

	void VulkanGraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}

