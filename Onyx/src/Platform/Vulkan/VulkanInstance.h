#ifndef _ONYX_PLATFORM_VULKAN_INSTANCE_H_
#define _ONYX_PLATFORM_VULKAN_INSTANCE_H_

#include <vulkan/vulkan.h>
#include <vector>

#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Onyx {

	//TODO: add debug release toggle
#ifdef _ONYX_DEBUG_
	inline bool KHR_EnableValidationLayers = true;
#else
	inline bool KHR_EnableValidationLayers = false;
#endif

	inline const std::vector<const char*> KHR_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	class VulkanInstance {
	
	private:
		VulkanInstance();
		static VulkanInstance* s_Instance;
	public:
		~VulkanInstance();
		static VulkanInstance* get();
		const VkInstance& getVkInstance() const { return m_VkInstance; };

		void setGLFWwindow(GLFWwindow* window) const { m_WindowHandle = window; };
		GLFWwindow* getGLFWwindow() const { return (GLFWwindow*)m_WindowHandle; };
		bool validationLayersEnabled() const { return KHR_EnableValidationLayers; };

	private:
		static GLFWwindow* m_WindowHandle;
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