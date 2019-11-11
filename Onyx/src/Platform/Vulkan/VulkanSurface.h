#ifndef _ONYX_PLATFORM_VULKAN_SURFACE_H_
#define _ONYX_PLATFORM_VULKAN_SURFACE_H_

#include "vulkan/vulkan.h"
#include "VulkanInstance.h"

namespace Onyx {

	class VulkanSurface {

	public:

		VulkanSurface(const VkInstance& vkInstance);
		~VulkanSurface();
		const VkSurfaceKHR& getVkSurfaceKHR() { return m_VkSurface; };
		
	private:
		VkInstance m_VkInstance;
		VkSurfaceKHR m_VkSurface;
		//friend class VulkanInstance;
	};


}

#endif // _ONYX_PLATFORM_VULKAN_SURFACE_H_
