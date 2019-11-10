#ifndef _ONYX_PLATFORM_VULKAN_INSTANCE_H_
#define _ONYX_PLATFORM_VULKAN_INSTANCE_H_

#include <Onyx/graphics/RendererAPI.h>
#include <vulkan/vulkan.h>

namespace Onyx {
	class VulkanInstance {
	public:

		VulkanInstance();
		~VulkanInstance();
		void init();
	private:
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		#ifdef _ONYX_DEBUG_
		const bool m_EnableValidationLayers = true;
		#else
		const bool m_EnableValidationLayers = false;
		#endif

		VkInstance m_VkInstance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
	};
}




#endif // !_ONYX_PLATFORM_VULKAN_INSTANCE_H_