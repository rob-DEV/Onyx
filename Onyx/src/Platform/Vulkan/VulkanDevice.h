#ifndef _ONYX_PLATFORM_VULKAN_DEVICE_H_
#define _ONYX_PLATFORM_VULKAN_DEVICE_H_

#include "VulkanInstance.h"
#include <vulkan/vulkan.h>

#include <optional>



namespace Onyx {

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class VulkanDevice {
	private:
		VulkanDevice();
		static VulkanDevice* s_Instance;
	public:
		~VulkanDevice();
		static VulkanDevice* get();
		const VkPhysicalDevice& getPhysicalDevice() const { return m_PhysicalDevice; };
		const VkDevice& getLogicalDevice() const { return m_Device; };

	private:
		void pickPhysicalDevice();
		void createLogicalDevice();
		
		//VULKAN OBJECTS
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

		//HELPER METHODS
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	};


}



#endif // !_ONYX_PLATFORM_VULKAN_DEVICE_H_
