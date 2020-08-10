#ifndef _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_
#define _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_

#include <vulkan/vulkan.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Onyx {

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;
	
		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription = {};

			bindingDescription.binding = 0; //starting index of data (per vertex)
			bindingDescription.stride = sizeof(Vertex); //distance between each Vertex structure
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			
			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {

			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

			/*
				float: VK_FORMAT_R32_SFLOAT
				vec2: VK_FORMAT_R32G32_SFLOAT
				vec3: VK_FORMAT_R32G32B32_SFLOAT
				vec4: VK_FORMAT_R32G32B32A32_SFLOAT

				ivec2: VK_FORMAT_R32G32_SINT, a 2-component vector of 32-bit signed integers
				uvec4: VK_FORMAT_R32G32B32A32_UINT, a 4-component vector of 32-bit unsigned integers
				double: VK_FORMAT_R64_SFLOAT
			*/

			//LIKE VERTEX ATTRIBUTE POINTER
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}

	};

	/*inline std::vector<Vertex> vertices = {
	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{0.3f, -0.3f}, {1.0f, 0.0f, 0.0f}},
	{{0.3f, 0.3f}, {0.8f, 0.2f, 0.56f}},
	{{-0.3f, 0.3f}, {0.4f, 0.1f, 0.2f}},
	{{0.6f, -0.1f}, {0.1f, 0.7f, 0.3f}},
	{{0.7f, 0.1f}, {0.2f, 0.2f, 0.3f}},
	{{0.5f, 0.1f}, {0.4f, 0.2f, 0.7f}}
	};*/

	inline std::vector<Vertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	inline std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
	};

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

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
		
		void setViewMatrixTest(const glm::mat4& matrix) { m_ViewMatrix = matrix; };
		void drawFrame();

	private:
		void createSwapchain();
		void cleanupSwapchain();
		void recreateSwapchain();
		void createImageViews();
		void createRenderPass();
		void createDescriptorSetLayout();
		void createDescriptorPool();
		void createDescriptorSets();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createVertexBuffer();
		void createUniformBuffers();
		void updateUniformBuffers(uint32_t imageIndex);
		void createCommandBuffers();
		void createSyncObjects();


		glm::mat4 m_ViewMatrix;
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

		VkDescriptorSetLayout m_DescriptorSetLayout;
		VkDescriptorPool m_DescriptorPool;
		std::vector<VkDescriptorSet> m_DescriptorSets;

		VkPipelineLayout m_PipelineLayout;
		VkRenderPass m_RenderPass;
		VkPipeline m_GraphicsPipeline;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers;

		VkCommandPool m_CommandPool;
		std::vector<VkCommandBuffer> m_CommandBuffers;

		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;


		VkClearValue m_ClearColor = { 0.2f, 0.2f, 0.2f, 0.2f };

		//HELPER METHODS
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		VkShaderModule createShaderModule(const std::vector<char>& code);

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	};
}

#endif // _ONYX_PLATFORM_VULKAN_SWAPCHAIN_H_
