#ifndef _ONYX_PLATFORM_VULKAN_DEVICE_H_
#define _ONYX_PLATFORM_VULKAN_DEVICE_H_

#include "vulkan/vulkan.h"
#include "VulkanInstance.h"
#include <optional>

namespace Onyx {

	class VulkanDevice {
	public:
		VulkanDevice(VulkanInstance* vulkanInstance, bool useValidationLayers);
		~VulkanDevice();
	
	private:
		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete() {
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surfaceKHR);
		const std::vector<const char*> validationLayers = {	"VK_LAYER_KHRONOS_validation" };

	private:

		friend class VulkanInstance;

		//VK MEMBERS
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_LogicalDevice = VK_NULL_HANDLE;
		VkQueue m_GraphicsQueue = VK_NULL_HANDLE; 


	};
}

#endif // _ONYX_PLATFORM_VULKAN_DEVICE_H_
