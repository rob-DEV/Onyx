#ifndef _ONYX_PLATFORM_VULKAN_RENDERER_API_H_
#define _ONYX_PLATFORM_VULKAN_RENDERER_API_H_

#include <Onyx/graphics/RendererAPI.h>

namespace Onyx {
	class VulkanRendererAPI : public RendererAPI {
	public:

		void init();
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void setClearColor(const glm::vec4& color);
		void clear();

	};
}

#endif // !_ONYX_PLATFORM_VULKAN_RENDERER_API_H_
