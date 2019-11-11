#ifndef _ONYX_PLATFORM_VULKAN_GRAPHICS_CONTEXT_H_
#define _ONYX_PLATFORM_VULKAN_GRAPHICS_CONTEXT_H_

#include <Onyx/graphics/GraphicsContext.h>
#include <Platform/Vulkan/VulkanInstance.h>

struct GLFWwindow;

namespace Onyx {

	class VulkanGraphicsContext : public GraphicsContext {

	public:
		
		VulkanGraphicsContext(GLFWwindow* window);
		virtual ~VulkanGraphicsContext();
		void init();
		void swapBuffers();

	private:
		VulkanInstance* m_VulkanInstance = NULL;
		GLFWwindow* m_WindowHandle;

	};


}


#endif // _ONYX_PLATFORM_VULKAN_GRAPHICS_CONTEXT_H_
