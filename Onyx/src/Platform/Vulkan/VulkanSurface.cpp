#include "onyxpch.h"
#include "VulkanSurface.h"
#include "VulkanInstance.h"

#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32


#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan_win32.h>

#include <Onyx/Core/Application.h>

namespace Onyx {

	VulkanSurface* VulkanSurface::s_Instance = NULL; 

	VulkanSurface::VulkanSurface()
	{

		if (glfwCreateWindowSurface(VulkanInstance::get()->getVkInstance(), VulkanInstance::get()->getGLFWwindow(), nullptr, &m_VkSurface) != VK_SUCCESS) {
			printf("VulkanSurface.cpp 22 : Failed to create GLFW VkSurface\n");
			assert(false);
		}

		//SET VulkanSurface static member as this (Only ever allow one VkSurface per application (only one window per onyx))
		s_Instance = this;
	}

	VulkanSurface::~VulkanSurface()
	{
		vkDestroySurfaceKHR(VulkanInstance::get()->getVkInstance(), m_VkSurface, nullptr);
	}
	
	VulkanSurface* VulkanSurface::get()
	{
		if(s_Instance == NULL)
			s_Instance = new VulkanSurface();
		
		return s_Instance;
	}

}