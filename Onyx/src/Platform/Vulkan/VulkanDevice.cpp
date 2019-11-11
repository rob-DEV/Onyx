#include "onyxpch.h"

#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include <optional>

static std::unordered_map<int, std::string> s_gpuVendors;

namespace Onyx {

	bool VulkanDevice::isDeviceSuitable(VkPhysicalDevice device) {
		
		QueueFamilyIndices indices = findQueueFamilies(device);

		return indices.isComplete();
	}
	
	VulkanDevice::QueueFamilyIndices VulkanDevice::findQueueFamilies(VkPhysicalDevice device) {
		
		VulkanDevice::QueueFamilyIndices indices = { 0 };

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			i++;
		}

		return indices;
	}

	VulkanDevice::VulkanDevice(const VkInstance& vkInstance, bool useValidationLayers)
	{

		//CREATE PHYSICAL DEVICE 
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);
		
		if (deviceCount == 0) {
			printf("Failed to find a GPU with Vulkan Support : VulkanDevice.cpp : 48\n");
			assert(false);
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());
		
		for (const auto& device : devices) {
			if (isDeviceSuitable(device)) {
				m_PhysicalDevice = device;
				break;
			}
		}

		if (m_PhysicalDevice == VK_NULL_HANDLE) {
			printf("Failed to create physical device : VulkanDevice.cpp : 63\n");
			assert(false);
		}

		s_gpuVendors[0x1002] = "AMD";
		s_gpuVendors[0x10DE] = "Nvidia Corporation";
		s_gpuVendors[0x8086] = "Intel (R) Graphics";
		s_gpuVendors[0x13B5] = "ARM";

		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProperties);
		std::cout << "Vulkan GPU Info:\n";

		std::cout << "\tDevice Name:" <<  deviceProperties.deviceName << "\n";
		std::cout << "\tVendor:" << s_gpuVendors[deviceProperties.vendorID] <<"\n";

		//CREATE LOGICAL DEVICE 
		QueueFamilyIndices indices = findQueueFamilies(m_PhysicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		//TODO: add specific features
		VkPhysicalDeviceFeatures deviceFeatures = {};
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = 0;
		
		if (useValidationLayers) {
			
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS) {
			printf("Failed to create logical device : VulkanDevice.cpp : 114\n");
			assert(false);
		}

		vkGetDeviceQueue(m_LogicalDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);

	}

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(m_LogicalDevice, nullptr);
	}

}