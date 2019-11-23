#ifndef _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_
#define _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_

#include <vulkan/vulkan.h>

namespace Onyx {

	class VulkanSwapchain {
	private:
		VulkanSwapchain();
		static VulkanSwapchain* s_Instance;
	public:
		~VulkanSwapchain();
		static VulkanSwapchain* get();
		const std::vector<VkFramebuffer> getFrameBuffers() const { return m_SwapChainFramebuffers; };
		const VkRenderPass& getRenderPass() const { return m_RenderPass; };
		const VkExtent2D& getExtent() const { return m_SwapChainExtent; };
		const VkPipeline& getGraphicsPipeline() const { return m_GraphicsPipeline; };

		void drawFrame();

	private:
		void createSwapchain();
		void cleanupSwapchain();
		void recreateSwapchain();
		void createImageViews();
		void createRenderPass();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();

		const int MAX_FRAMES_IN_FLIGHT = 2;
		size_t m_CurrentFrame = 0;
		std::vector<VkFence> m_InFlightFences;
		std::vector<VkFence> m_ImagesInFlight;

		//VULKAN OBJECTS
		const VkDevice& m_LogicalDeviceReference;
		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;
		std::vector<VkImageView> m_SwapChainImageViews;

		VkPipelineLayout m_PipelineLayout;
		VkRenderPass m_RenderPass;
		VkPipeline m_GraphicsPipeline;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;

		VkCommandPool m_CommandPool;
		std::vector<VkCommandBuffer> m_CommandBuffers;

		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;


		//HELPER METHODS
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		VkShaderModule createShaderModule(const std::vector<char>& code);
	};


}


#endif // _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_
