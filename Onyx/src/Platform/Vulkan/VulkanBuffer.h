#ifndef _ONYX_PLATFORM_VULKAN_BUFFER_H_
#define _ONYX_PLATFORM_VULKAN_BUFFER_H_

#include <Onyx/graphics/Buffer.h>

#include <vulkan/vulkan.h>

namespace Onyx {
	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(float* vertices, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
		virtual ~VulkanVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

		inline const VkBuffer& GetBufferObject() const { return m_Buffer; };
		inline const VkDeviceMemory& GetBufferMemory() const { return m_BufferMemory; };

	private:
		BufferLayout m_Layout;
		VkBuffer m_Buffer;
		VkDeviceMemory m_BufferMemory;
	};

	class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);

		virtual ~VulkanIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		inline const VkBuffer& GetBufferObject() const { return m_Buffer; };
		inline const VkDeviceMemory& GetBufferMemory() const { return m_BufferMemory; };

	private:
		VkBuffer m_Buffer;
		VkDeviceMemory m_BufferMemory;
	};

}



#endif // !_ONYX_PLATFORM_VULKAN_BUFFER_H_
