#ifndef _ONYX_PLATFORM_VULKAN_BUFFER_H_
#define _ONYX_PLATFORM_VULKAN_BUFFER_H_

#include <Onyx/graphics/Buffer.h>

#include <vulkan/vulkan.h>

namespace Onyx {
	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(float* vertices, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
		virtual ~VulkanVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		inline const VkBuffer& getBufferObject() const { return m_Buffer; };

	private:
		VkBuffer m_Buffer;
		VkDeviceMemory m_BufferMemory;
	};

	class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~VulkanIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual uint32_t getCount() const { return m_Count; }
	private:
		VkBuffer m_RendererID;
		uint32_t m_Count;
	};

}



#endif // !_ONYX_PLATFORM_VULKAN_BUFFER_H_
