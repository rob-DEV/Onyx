#ifndef _ONYX_PLATFORM_VULKAN_BUFFER_H_
#define _ONYX_PLATFORM_VULKAN_BUFFER_H_

#include <Onyx/graphics/Buffer.h>

namespace Onyx {
	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(float* vertices, uint32_t size);
		virtual ~VulkanVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

	private:
		uint32_t m_RendererID;
	};

	class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~VulkanIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual uint32_t getCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}



#endif // !_ONYX_PLATFORM_VULKAN_BUFFER_H_
