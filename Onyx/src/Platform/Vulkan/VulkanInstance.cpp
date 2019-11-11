#include "onyxpch.h"

#include "VulkanInstance.h"
#include "VulkanDevice.h"

#include <GLFW/glfw3.h>

namespace Onyx {

	std::vector<const char*> VulkanInstance::getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (m_EnableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		//VULKAN DEBUG MESSENGER CALLBACK FUNCTION	
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	VulkanInstance::VulkanInstance()
	{
		init();
	}

	void VulkanInstance::init()
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Onyx Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Onyx";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		std::vector<const char*> creation_extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (m_EnableValidationLayers) {

			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


			for (const char* layerName : validationLayers) {
				bool layerFound = false;

				std::cout << "available layers:" << std::endl;

				for (const auto& layerProperties : availableLayers) {
					std::cout << "\t" << layerProperties.layerName << std::endl;
					if (strcmp(layerName, layerProperties.layerName) == 0) {
						layerFound = true;
						break;
					}
				}

				if (!layerFound) {
					std::cout << "Error : Vulkan Validation Layers requested but not available!" << std::endl;
					system("PAUSE");
				}
			}

			//if here all good with regards to validation
			//TODO: refactor
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();

			//add debug message callback		
			creation_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			//add all in extensions to be used, including validation layers and debug to VK instance creation info
			createInfo.enabledExtensionCount = static_cast<uint32_t>(creation_extensions.size());
			createInfo.ppEnabledExtensionNames = creation_extensions.data();

		}

		if (vkCreateInstance(&createInfo, nullptr, &m_VkInstance) != VK_SUCCESS)
			printf("Failed to create Vulkan Instance : VulkanInstance.cpp 39\n");
		else
			printf("Vulkan Instance - Successfully Created : VulkanInstance.cpp 41\n");


		//create and point the VkDebugUtilsMessengerEXT to the call back function
		VkDebugUtilsMessengerCreateInfoEXT createDebugUtilsMessangerInfo = {};
		createDebugUtilsMessangerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createDebugUtilsMessangerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createDebugUtilsMessangerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createDebugUtilsMessangerInfo.pfnUserCallback = debugCallback;
		createDebugUtilsMessangerInfo.pUserData = nullptr;

		//create the messenger
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDebugUtilsMessengerEXT");
		VkResult createDebugUtilsMessangerInfoResult = VK_SUCCESS;

		if (func != nullptr) {
			createDebugUtilsMessangerInfoResult = func(m_VkInstance, &createDebugUtilsMessangerInfo, nullptr, &m_DebugMessenger);
		}
		else {
			printf("Failed to create vkDebugUtilsMessenger : VK_ERROR_EXTENSION_NOT_PRESENT\n");
		}

		if (createDebugUtilsMessangerInfoResult)
			printf("Failed to setup vkDebugUtilsMessenger\n");

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "available extensions:" << std::endl;

		for (const auto& extension : extensions)
			std::cout << "\t" << extension.extensionName << std::endl;


		//create physical and logical devices
		m_VulkanDevice = new VulkanDevice(m_VkInstance, m_EnableValidationLayers);

	}
	VulkanInstance::~VulkanInstance()
	{
		vkDestroyInstance(m_VkInstance, nullptr);

	}
}