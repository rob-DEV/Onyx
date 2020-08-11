#ifndef _ONYX_PLATFORM_VULKAN_DEVICE_H_
#define _ONYX_PLATFORM_VULKAN_DEVICE_H_

#include "VulkanInstance.h"
#include <vulkan/vulkan.h>

#include <optional>

namespace Onyx {

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};


	class VulkanDevice {
	public:
		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool IsComplete() {
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities = {0};
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

	private:
		VulkanDevice();
		static VulkanDevice* s_Instance;
	public:
		~VulkanDevice();
		static VulkanDevice* Get();
		const VkPhysicalDevice& GetPhysicalDevice() const { return m_PhysicalDevice; };
		const VkDevice& GetLogicalDevice() const { return m_Device; };
		const VkQueue& GetGraphicsQueue() const { return m_GraphicsQueue; };
		const VkQueue& GetPresentQueue() const { return m_PresentQueue; };

	private:
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		
		//VULKAN OBJECTS
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

	public:
		//HELPER METHODS
		bool IsDeviceSuitable(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	};


}



#endif // !_ONYX_PLATFORM_VULKAN_DEVICE_H_
