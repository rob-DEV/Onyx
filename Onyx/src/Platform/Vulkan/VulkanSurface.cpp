#include "onyxpch.h"
#include "VulkanSurface.h"

#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32


#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "vulkan/vulkan_win32.h"

#include <Onyx/Core/Application.h>

namespace Onyx {

	VulkanSurface::VulkanSurface(const VkInstance& vkInstance) : m_VkInstance(vkInstance)
	{
		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		//createInfo.hwnd = glfwGetWin32Window((GLFWwindow*)Application::get()->getOnyxWindow()->getNativeWindow());
		createInfo.hinstance = GetModuleHandle(nullptr);

		if (vkCreateWin32SurfaceKHR(vkInstance, &createInfo, nullptr, &m_VkSurface) != VK_SUCCESS) {
			printf("Vulkan Graphics Context : Failed to create VkWin32SurfaceKHR: VulkanGraphicsContext.cpp 46\n");
			assert(false);
		}

		printf("VkSurfaceWin32SurfaceKHR created successfully!\n");

	}

	VulkanSurface::~VulkanSurface()
	{
		vkDestroySurfaceKHR(m_VkInstance, m_VkSurface, nullptr);
	}

}