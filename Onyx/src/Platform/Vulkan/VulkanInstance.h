#ifndef _ONYX_PLATFORM_VULKAN_INSTANCE_H_
#define _ONYX_PLATFORM_VULKAN_INSTANCE_H_

#include <vulkan/vulkan.h>
#include <vector>

namespace Onyx {

	//TODO: add debug release toggle
	inline bool KHR_EnableValidationLayers = true;
	inline const std::vector<const char*> KHR_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	class VulkanInstance {
	private:
		VulkanInstance();
		static VulkanInstance* s_Instance;
	public:
		~VulkanInstance();
		static VulkanInstance* create();
		const VkInstance& getVkInstance() const { return m_VkInstance; };

	private:
		//VULKAN OBJECTS
		VkInstance m_VkInstance;
		VkDebugUtilsMessengerEXT m_VkDebugMessenger;


		//HELPER METHODS
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();

		//VULKAN VALIDATION LAYERS DEBUG CALLBACK
		static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstanceDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	};

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);


}

#endif // !_ONYX_PLATFORM_VULKAN_INSTANCE_H_