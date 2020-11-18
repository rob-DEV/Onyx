#include "onyxpch.h"
#include "VulkanSwapchain.h"
#include "VulkanDevice.h"
#include "VulkanSurface.h"


#include <Onyx/Core/Window.h>
#include <Onyx/Core/FileIO.h>
#include <Onyx/Graphics/RendererAPI.h>

#include "VulkanBuffer.h"



#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <chrono>

namespace Onyx {

	VulkanSwapchain* VulkanSwapchain::s_Instance = nullptr;
	VulkanVertexBuffer* vertexStagingBufferTest = nullptr;
	VulkanVertexBuffer* vertexBufferTest = nullptr;
	VulkanVertexBuffer* indiceBufferTest = nullptr;
	VulkanVertexBuffer* indiceStagingBufferTest = nullptr;

	std::vector<VulkanVertexBuffer*> uniformBuffers;

	VulkanSwapchain::VulkanSwapchain() 
		: m_LogicalDeviceReference(VulkanDevice::Get()->GetLogicalDevice())
	{

		//initialize view matrix
		m_ViewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));


		createSwapchain();
		createImageViews();
		createRenderPass();
		createDescriptorSetLayout();
		createGraphicsPipeline();
		createFramebuffers();
		createCommandPool();
		createVertexBuffer();

		createUniformBuffers();
		createDescriptorPool();
		createDescriptorSets();

		createCommandBuffers();
		createSyncObjects();

		s_Instance = this;
	}


	VulkanSwapchain::~VulkanSwapchain()
	{
		cleanupSwapchain();

		for (size_t i = 0; i < m_SwapChainImages.size(); ++i) {
			delete uniformBuffers[i];
		}

		vkDestroyDescriptorPool(m_LogicalDeviceReference, m_DescriptorPool, nullptr);

		vkDestroyDescriptorSetLayout(m_LogicalDeviceReference, m_DescriptorSetLayout, nullptr);

		delete indiceBufferTest;
		delete vertexBufferTest;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
			vkDestroySemaphore(m_LogicalDeviceReference, m_RenderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(m_LogicalDeviceReference, m_ImageAvailableSemaphores[i], nullptr);
			vkDestroyFence(m_LogicalDeviceReference, m_InFlightFences[i], nullptr);
		}
	
		vkDestroyCommandPool(m_LogicalDeviceReference, m_CommandPool, nullptr);

	}

	VulkanSwapchain* VulkanSwapchain::Get()
	{
		if (s_Instance == nullptr)
			return new VulkanSwapchain();
		else
			return s_Instance;
	}

	void VulkanSwapchain::createSwapchain()
	{
		VulkanDevice::SwapChainSupportDetails swapChainSupport = VulkanDevice::Get()->QuerySwapChainSupport(VulkanDevice::Get()->GetPhysicalDevice());

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = VulkanSurface::Get()->GetVkSurface();

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		VulkanDevice::QueueFamilyIndices indices = VulkanDevice::Get()->FindQueueFamilies(VulkanDevice::Get()->GetPhysicalDevice());
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_LogicalDeviceReference, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 85 : Failed to create swapchain\n");
			assert(false);
		}

		vkGetSwapchainImagesKHR(m_LogicalDeviceReference, m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_LogicalDeviceReference, m_SwapChain, &imageCount, m_SwapChainImages.data());

		m_SwapChainImageFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}

	void VulkanSwapchain::cleanupSwapchain()
	{
		for (size_t i = 0; i < m_SwapChainFramebuffers.size(); ++i)
			vkDestroyFramebuffer(m_LogicalDeviceReference, m_SwapChainFramebuffers[i], nullptr);

		vkFreeCommandBuffers(m_LogicalDeviceReference, m_CommandPool, static_cast<uint32_t>(m_CommandBuffers.size()), m_CommandBuffers.data());

		vkDestroyPipeline(m_LogicalDeviceReference, m_GraphicsPipeline, nullptr);
		vkDestroyPipelineLayout(m_LogicalDeviceReference, m_PipelineLayout, nullptr);
		vkDestroyRenderPass(m_LogicalDeviceReference, m_RenderPass, nullptr);

		for (size_t i = 0; i < m_SwapChainImageViews.size(); ++i)
			vkDestroyImageView(m_LogicalDeviceReference, m_SwapChainImageViews[i], nullptr);

		vkDestroySwapchainKHR(m_LogicalDeviceReference, m_SwapChain, nullptr);


	}

	void VulkanSwapchain::recreateSwapchain()
	{
		vkDeviceWaitIdle(m_LogicalDeviceReference);

		cleanupSwapchain();

		createSwapchain();
		createImageViews();
		createRenderPass();
		createGraphicsPipeline();
		createFramebuffers();
		
		createUniformBuffers();
		createDescriptorPool();
		createDescriptorSets();

		createCommandBuffers();


	}

	VkSurfaceFormatKHR VulkanSwapchain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR VulkanSwapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		if (RendererAPI::VsyncEnabled())
			return VK_PRESENT_MODE_FIFO_KHR;

		//check for mailbox support else FIFO
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanSwapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {

			int width, height;
			glfwGetFramebufferSize(VulkanInstance::Get()->GetGLFWwindow(), &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			return actualExtent;
		}
	}

	VkShaderModule VulkanSwapchain::createShaderModule(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(m_LogicalDeviceReference, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 136 : Failed to create shader module\n");
			assert(false);
		}

		return shaderModule;
	}

	uint32_t VulkanSwapchain::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(VulkanDevice::Get()->GetPhysicalDevice(), &memProperties);
		
		for (uint32_t i = 0; i < memProperties.memoryTypeCount; ++i) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		printf("VulkanSwapchain.cpp findMemoryType : Failed to find suitable memory\n");
		assert(false);
	}

	void VulkanSwapchain::createImageViews()
	{
		m_SwapChainImageViews.resize(m_SwapChainImages.size());

		for (size_t i = 0; i < m_SwapChainImages.size(); ++i) {
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_SwapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_SwapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_LogicalDeviceReference, &createInfo, nullptr, &m_SwapChainImageViews[i]) != VK_SUCCESS) {
				printf("VulkanSwapchain.cpp 155 : Failed to create image views\n");
				assert(false);
			}
		}
	}

	void VulkanSwapchain::createRenderPass()
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = m_SwapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(m_LogicalDeviceReference, &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 155 : Failed to create render pass\n");
			assert(false);
		}
	}

	void VulkanSwapchain::createDescriptorSetLayout()
	{
		VkDescriptorSetLayoutBinding uboLayoutBinding = {};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.descriptorCount = 1;

		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

		VkDescriptorSetLayoutCreateInfo layoutInfo = {};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 1;
		layoutInfo.pBindings = &uboLayoutBinding;

		if (vkCreateDescriptorSetLayout(m_LogicalDeviceReference, &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp createDescriptorSetLayout : Failed to layout\n");
			assert(false);
		}

	}

	void VulkanSwapchain::createDescriptorPool()
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = static_cast<uint32_t>(m_SwapChainImages.size());

		VkDescriptorPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;

		poolInfo.maxSets = static_cast<uint32_t>(m_SwapChainImages.size());;


		if (vkCreateDescriptorPool(m_LogicalDeviceReference, &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp createDescriptorPool : Failed to create descriptor pool\n");
			assert(false);
		}

	}

	void VulkanSwapchain::createDescriptorSets()
	{
		std::vector<VkDescriptorSetLayout> layouts(m_SwapChainImages.size(), m_DescriptorSetLayout);
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(m_SwapChainImages.size());
		allocInfo.pSetLayouts = layouts.data();

		m_DescriptorSets.resize(m_SwapChainImages.size());
		if (vkAllocateDescriptorSets(m_LogicalDeviceReference, &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp createDescriptorSets : Failed to create descriptor sets\n");
			assert(false);
		}

		for (size_t i = 0; i < m_SwapChainImages.size(); ++i) {
			VkDescriptorBufferInfo bufferInfo = {};
			bufferInfo.buffer = uniformBuffers[i]->GetBufferObject();
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkWriteDescriptorSet descriptorWrite = {};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_DescriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;

			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrite.descriptorCount = 1;

			descriptorWrite.pBufferInfo = &bufferInfo;
			descriptorWrite.pImageInfo = nullptr; // Optional
			descriptorWrite.pTexelBufferView = nullptr; // Optional

			vkUpdateDescriptorSets(m_LogicalDeviceReference, 1, &descriptorWrite, 0, nullptr);

		}

		

	}

	void VulkanSwapchain::createGraphicsPipeline()
	{
		//read in shaders push to shader modules
		auto vertSprivSource = FileIO::ReadFileByte("res/shaders/vulkantest/vkvert.spv");
		auto fragSprivSource = FileIO::ReadFileByte("res/shaders/vulkantest/vkfrag.spv");


		VkShaderModule vertShaderModule = createShaderModule(vertSprivSource);
		VkShaderModule fragShaderModule = createShaderModule(fragSprivSource);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		//vertex attribute pointer like code
		//MODIFY VERTEX ATTRIBUTES TO ACCEPT Vertex structure
		auto bindingDescription = Vertex::getBindingDescription();
		auto attributeDescriptions = Vertex::GetAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
		
		
		//vertexInputInfo.vertexBindingDescriptionCount = 0;
		//vertexInputInfo.vertexAttributeDescriptionCount = 0;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport = {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)m_SwapChainExtent.width;
		viewport.height = (float)m_SwapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor = {};
		scissor.offset = { 0, 0 };
		scissor.extent = m_SwapChainExtent;

		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		//rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;		
		pipelineLayoutInfo.pushConstantRangeCount = 0;


		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &m_DescriptorSetLayout;

		if (vkCreatePipelineLayout(m_LogicalDeviceReference, &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 329 : Failed to create Pipeline Layout\n");
			assert(false);
		}

		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = m_PipelineLayout;
		pipelineInfo.renderPass = m_RenderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(m_LogicalDeviceReference, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 349 : Failed to create Graphics Pipeline\n");
			assert(false);
		}


		vkDestroyShaderModule(m_LogicalDeviceReference, fragShaderModule, nullptr);
		vkDestroyShaderModule(m_LogicalDeviceReference, vertShaderModule, nullptr);
	}

	void VulkanSwapchain::createFramebuffers()
	{
		m_SwapChainFramebuffers.resize(m_SwapChainImageViews.size());
		for (size_t i = 0; i < m_SwapChainImageViews.size(); ++i) {
			VkImageView attachments[] = {
				m_SwapChainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = m_SwapChainExtent.width;
			framebufferInfo.height = m_SwapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_LogicalDeviceReference, &framebufferInfo, nullptr, &m_SwapChainFramebuffers[i]) != VK_SUCCESS) {
				printf("VulkanSwapchain.cpp 376 : Failed to create Frame Buffer\n");
				assert(false);
			}
		}
	}

	void VulkanSwapchain::createCommandPool()
	{
		VulkanDevice::QueueFamilyIndices queueFamilyIndices = VulkanDevice::Get()->FindQueueFamilies(VulkanDevice::Get()->GetPhysicalDevice());

		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
		poolInfo.flags = 0; // Optional

		if (vkCreateCommandPool(m_LogicalDeviceReference, &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 329 : Failed to create Command Pool\n");
			assert(false);
		}
	}

	void VulkanSwapchain::createVertexBuffer()
	{
		VkDeviceSize vertBufferSize = sizeof(vertices[0]) * vertices.size();
		vertexStagingBufferTest = new VulkanVertexBuffer(reinterpret_cast<float*>(vertices.data()), vertBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	
		//staging buffer test
		//map vertex buffer
		void* data;
		vkMapMemory(VulkanDevice::Get()->GetLogicalDevice(), vertexStagingBufferTest->GetBufferMemory(), 0, vertBufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t)vertBufferSize);
		vkUnmapMemory(VulkanDevice::Get()->GetLogicalDevice(), vertexStagingBufferTest->GetBufferMemory());

		VkDeviceSize indiceBufferSize = sizeof(indices[0]) * indices.size();
		indiceStagingBufferTest = new VulkanVertexBuffer(reinterpret_cast<float*>(vertices.data()), vertBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		void* data1;
		vkMapMemory(VulkanDevice::Get()->GetLogicalDevice(), indiceStagingBufferTest->GetBufferMemory(), 0, indiceBufferSize, 0, &data1);
		memcpy(data1, &indices[0], (size_t)indiceBufferSize);
		vkUnmapMemory(VulkanDevice::Get()->GetLogicalDevice(), indiceStagingBufferTest->GetBufferMemory());

		vertexBufferTest = new VulkanVertexBuffer(NULL, vertBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		indiceBufferTest = new VulkanVertexBuffer(reinterpret_cast<float*>(indices.data()), indiceBufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);




		//copy staging buffer (CPU) to Vertex Buffer on GPU
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_CommandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(VulkanDevice::Get()->GetLogicalDevice(), &allocInfo, &commandBuffer);
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy vertCopyRegion = {};
		vertCopyRegion.srcOffset = 0; // Optional
		vertCopyRegion.dstOffset = 0; // Optional
		vertCopyRegion.size = vertBufferSize;
		vkCmdCopyBuffer(commandBuffer, vertexStagingBufferTest->GetBufferObject(), vertexBufferTest->GetBufferObject(), 1, &vertCopyRegion);

		VkBufferCopy indiceCopyRegion = {};
		indiceCopyRegion.srcOffset = 0; // Optional
		indiceCopyRegion.dstOffset = 0; // Optional
		indiceCopyRegion.size = indiceBufferSize;

		vkCmdCopyBuffer(commandBuffer, indiceStagingBufferTest->GetBufferObject(), indiceBufferTest->GetBufferObject(), 1, &indiceCopyRegion);


		vkEndCommandBuffer(commandBuffer);

		//execute the command buffer copy command
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(VulkanDevice::Get()->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(VulkanDevice::Get()->GetGraphicsQueue());

		vkFreeCommandBuffers(VulkanDevice::Get()->GetLogicalDevice(), m_CommandPool, 1, &commandBuffer);

		//cleanup VSB
		delete vertexStagingBufferTest;
		delete indiceStagingBufferTest;
	
	}


	void VulkanSwapchain::createUniformBuffers()
	{

		uniformBuffers.resize(m_SwapChainImages.size());

		for (size_t i = 0; i < m_SwapChainImages.size(); ++i) {
			uniformBuffers[i] = new VulkanVertexBuffer(NULL, sizeof(UniformBufferObject), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		}
		
	}

	void VulkanSwapchain::updateUniformBuffers(uint32_t imageIndex)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo = {};

		ubo.model = m_ViewMatrix;

		ubo.view = glm::mat4(1.0f);


		ubo.proj = m_ViewMatrix;
		//ubo.proj = glm::ortho(glm::radians(45.0f), m_SwapChainExtent.width / (float)m_SwapChainExtent.height, 0.1f, 10.0f);

		ubo.proj[1][1] *= -1;

		void* data;
		vkMapMemory(m_LogicalDeviceReference, uniformBuffers[imageIndex]->GetBufferMemory(), 0, sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(m_LogicalDeviceReference, uniformBuffers[imageIndex]->GetBufferMemory());
	}

	void VulkanSwapchain::createCommandBuffers()
	{
		m_CommandBuffers.resize(m_SwapChainFramebuffers.size());

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_CommandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

		if (vkAllocateCommandBuffers(m_LogicalDeviceReference, &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 329 : Failed to allocate Command Buffer\n");
			assert(false);
		}

		for (size_t i = 0; i < m_CommandBuffers.size(); ++i) {
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(m_CommandBuffers[i], &beginInfo) != VK_SUCCESS) {
				printf("VulkanSwapchain.cpp 417 : Failed to begin recording Command Buffer\n");
				assert(false);
			}

			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_RenderPass;
			renderPassInfo.framebuffer = m_SwapChainFramebuffers[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = m_SwapChainExtent;

			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &m_ClearColor;

			vkCmdBeginRenderPass(m_CommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_CommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
			VkBuffer vertexBuffers[] = { vertexBufferTest->GetBufferObject() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(m_CommandBuffers[i], 0, 1, vertexBuffers, offsets);
			
			
			vkCmdBindIndexBuffer(m_CommandBuffers[i], indiceBufferTest->GetBufferObject(), 0, VK_INDEX_TYPE_UINT16);

			vkCmdBindDescriptorSets(m_CommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_PipelineLayout, 0, 1, &m_DescriptorSets[i], 0, nullptr);
			//vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

			vkCmdDrawIndexed(m_CommandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
			//vkCmdDraw(m_CommandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);
			
			vkCmdEndRenderPass(m_CommandBuffers[i]);

			if (vkEndCommandBuffer(m_CommandBuffers[i]) != VK_SUCCESS) {
				printf("VulkanSwapchain.cpp 441 : Failed to record Command Buffer\n");
				assert(false);
			}
		}
	}

	void VulkanSwapchain::createSyncObjects()
	{
		m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		m_ImagesInFlight.resize(m_SwapChainImages.size(), VK_NULL_HANDLE);

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
			if (vkCreateSemaphore(m_LogicalDeviceReference, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_LogicalDeviceReference, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(m_LogicalDeviceReference, &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {

				printf("VulkanSwapchain.cpp 441 : Failed to sync objects for a frame\n");
				assert(false);
			}
		}
	}

	void VulkanSwapchain::DrawFrame()
	{
		vkWaitForFences(m_LogicalDeviceReference, 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(m_LogicalDeviceReference, m_SwapChain, 
			UINT64_MAX, m_ImageAvailableSemaphores[m_CurrentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return;
		}
		else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			printf("VulkanSwapchain.cpp 518 : Failed to acquire swapchain image\n");
			assert(false);
		}

		if (m_ImagesInFlight[imageIndex] != VK_NULL_HANDLE) {
			vkWaitForFences(m_LogicalDeviceReference, 1, &m_ImagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
		}
		m_ImagesInFlight[imageIndex] = m_InFlightFences[m_CurrentFrame];

		//update uniform buffers
		updateUniformBuffers(imageIndex);


		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphores[m_CurrentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_CommandBuffers[imageIndex];

		VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphores[m_CurrentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;
		
		vkResetFences(m_LogicalDeviceReference, 1, &m_InFlightFences[m_CurrentFrame]);

		if (vkQueueSubmit(VulkanDevice::Get()->GetGraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 500 : Failed to submit draw to the Command Buffer\n");
			assert(false);
		}

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { m_SwapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		VkResult presentResult = vkQueuePresentKHR(VulkanDevice::Get()->GetGraphicsQueue(), &presentInfo);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
			recreateSwapchain();
		}
		else if (result != VK_SUCCESS) {
			printf("VulkanSwapchain.cpp 568 : Failed to present swapchain image\n");
			assert(false);
		}

		m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

}