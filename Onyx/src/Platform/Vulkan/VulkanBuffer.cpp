#include "onyxpch.h"
#include "VulkanBuffer.h"

#include "VulkanDevice.h"

namespace Onyx {

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(VulkanDevice::get()->getPhysicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		printf("VulkanBuffer.cpp findMemoryType : Failed to find suitable memory\n");
		assert(false);
	}

	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
	{
		VkDevice device = VulkanDevice::get()->getLogicalDevice();
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(device, &bufferInfo, nullptr, &m_Buffer) != VK_SUCCESS) {
			printf("VulkanBuffer.cpp VulkanVertexBuffer : Failed to create VulkanVertexBuffer\n");
			assert(false);
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, m_Buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(device, &allocInfo, nullptr, &m_BufferMemory) != VK_SUCCESS) {
			printf("VulkanBuffer.cpp VulkanVertexBuffer : Failed to allocate VulkanVertexBuffer memory\n");
			assert(false);
		}

		vkBindBufferMemory(VulkanDevice::get()->getLogicalDevice(), m_Buffer, m_BufferMemory, 0);

		//void* data;
		//vkMapMemory(device, m_BufferMemory, 0, size, 0, &data);
		//memcpy(data, &vertices[0], (size_t)size);
		//vkUnmapMemory(device, m_BufferMemory);

	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		vkDestroyBuffer(VulkanDevice::get()->getLogicalDevice(), m_Buffer, nullptr);
		vkFreeMemory(VulkanDevice::get()->getLogicalDevice(), m_BufferMemory, nullptr);
	}

	void VulkanVertexBuffer::bind() const
	{
		
	}

	void VulkanVertexBuffer::unbind() const
	{
		

	}
	
}