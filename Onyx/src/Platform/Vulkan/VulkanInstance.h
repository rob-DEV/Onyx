#ifndef _ONYX_PLATFORM_VULKAN_INSTANCE_H_
#define _ONYX_PLATFORM_VULKAN_INSTANCE_H_

#include <Onyx/graphics/RendererAPI.h>
#include <vulkan/vulkan.h>

#include <vector>

namespace Onyx {

	class VulkanDevice;
	
	class VulkanInstance {
	public:
		VulkanInstance();
		~VulkanInstance();
		void init();
		std::vector<const char*> getRequiredExtensions();

	private:

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		#ifdef _ONYX_DEBUG_
				const bool m_EnableValidationLayers = true;
		#else
				const bool m_EnableValidationLayers = false;
		#endif

		VulkanDevice* m_VulkanDevice;
		
		//VK MEMBERS
		VkInstance m_VkInstance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
	};
}

#endif // !_ONYX_PLATFORM_VULKAN_INSTANCE_H_