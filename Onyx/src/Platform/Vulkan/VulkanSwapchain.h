#ifndef _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_
#define _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_

#include <vulkan/vulkan.h>

namespace Onyx {

	class VulkanSwapchain {
	private:
		VulkanSwapchain();
		~VulkanSwapchain();
		
		VkSwapchainKHR m_Swapchain;
	public:
		const VkSwapchainKHR& getSwapChain() { return m_Swapchain; };
	};


}


#endif // _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_
