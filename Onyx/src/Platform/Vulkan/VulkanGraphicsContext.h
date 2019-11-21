#ifndef _ONYX_PLATFORM_VULKAN_GRAPHICS_CONTEXT_H_
#define _ONYX_PLATFORM_VULKAN_GRAPHICS_CONTEXT_H_

#include <Onyx/graphics/GraphicsContext.h>

#include <Platform/Vulkan/VulkanInstance.h>
#include <Platform/Vulkan/VulkanSurface.h>
#include <Platform/Vulkan/VulkanDevice.h>



namespace Onyx {

	class VulkanGraphicsContext : public GraphicsContext {
	public:

		VulkanGraphicsContext(GLFWwindow* window);
		virtual ~VulkanGraphicsContext();
		void init();
		void swapBuffers();

	private:
		VulkanInstance* m_VulkanInstance;
		VulkanSurface* m_VulkanSurface;
		GLFWwindow* m_WindowHandle;

	};


}


#endif // _ONYX_PLATFORM_VULKAN_GRAPHICS_CONTEXT_H_
