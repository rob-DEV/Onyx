#ifndef _ONYX_PLATFORM_VULKAN_INSTANCE_H_
#define _ONYX_PLATFORM_VULKAN_INSTANCE_H_

#include <Onyx/graphics/RendererAPI.h>
#include <vulkan/vulkan.h>

#include <vector>

struct GLFWwindow;

namespace Onyx {

	class VulkanDevice;
	
	class VulkanInstance {
	public:
		VulkanInstance(GLFWwindow* m_WindowHandle);
		~VulkanInstance();
		void init();
		std::vector<const char*> getRequiredExtensions();

	private:

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

		#ifdef _ONYX_DEBUG_
				const bool m_EnableValidationLayers = true;
		#else
				const bool m_EnableValidationLayers = false;
		#endif

		VulkanDevice* m_VulkanDevice;
		GLFWwindow* m_WindowHandle;
		//VK MEMBERS
		VkInstance m_VkInstance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		VkSurfaceKHR m_VkSurfaceKHR = VK_NULL_HANDLE;

		friend class VulkanDevice;
	};
}

#endif // !_ONYX_PLATFORM_VULKAN_INSTANCE_H_