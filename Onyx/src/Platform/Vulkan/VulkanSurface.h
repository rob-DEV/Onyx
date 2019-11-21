#ifndef _ONYX_PLATFORM_VULKAN_SURFACE_H_
#define _ONYX_PLATFORM_VULKAN_SURFACE_H_

#include "VulkanInstance.h"
#include <vulkan/vulkan.h>
#include <vector>

struct GLFWwindow;

namespace Onyx {

	class VulkanSurface {
	private:
		VulkanSurface(GLFWwindow* windowHandle);
		static VulkanSurface* s_Instance;
	public:
		~VulkanSurface();
		static VulkanSurface* create(GLFWwindow* windowHandle);
		const VkSurfaceKHR& getVkSurface() const { return m_VkSurface; };

	private:
		//VULKAN OBJECTS
		VkSurfaceKHR m_VkSurface;
	};

}

#endif // !_ONYX_PLATFORM_VULKAN_SURFACE_H_