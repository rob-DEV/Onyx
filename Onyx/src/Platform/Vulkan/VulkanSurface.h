#ifndef _ONYX_PLATFORM_VULKAN_SURFACE_H_
#define _ONYX_PLATFORM_VULKAN_SURFACE_H_


#include <vulkan/vulkan.h>

namespace Onyx {

	class VulkanSurface {
	private:
		VulkanSurface();
		static VulkanSurface* s_Instance;
	public:
		~VulkanSurface();
		static VulkanSurface* Get();
		const VkSurfaceKHR& GetVkSurface() const { return m_VkSurface; };

	private:
		VkSurfaceKHR m_VkSurface;
	};

}

#endif // !_ONYX_PLATFORM_VULKAN_SURFACE_H_