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
		delete m_VulkanSwapchain;
		delete m_VulkanDevice;
		delete m_VulkanSurface;
		delete m_VulkanInstance;
	}

	void VulkanGraphicsContext::Init()
	{
		std::cout << "\nVulkan Context Initialization\n";

		//creates and assigns the initial vkInstance 
		m_VulkanInstance = VulkanInstance::Get();
		m_VulkanInstance->SetGLFWwindow(m_WindowHandle);
		m_VulkanSurface = VulkanSurface::Get();
		m_VulkanDevice = VulkanDevice::Get();
		m_VulkanSwapchain = VulkanSwapchain::Get();

		std::cout << "Vulkan Initialization End!\n";
	}

	void VulkanGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}

