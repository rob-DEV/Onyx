#include "onyxpch.h"
#include "VulkanRenderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.h>
#include <Onyx/Graphics/VertexArray.h>



#include "VulkanInstance.h"
#include "VulkanDevice.h"
#include "VulkanShader.h"
#include "VulkanSwapchain.h"


struct Data {
	Onyx::VertexArray* VA;
	Onyx::OpenGLShader* SH;
	Onyx::Texture* WhiteTexture;
};

namespace Onyx {
	
	static Data* s_Data;

	void VulkanRenderer2D::initImplementation()
	{
		
	}

	void VulkanRenderer2D::destroyImplementation()
	{

	}

	void VulkanRenderer2D::beginSceneImplementation(const OrthographicCamera& camera)
	{

	}

	void VulkanRenderer2D::endSceneImplementation()
	{

	}

	void VulkanRenderer2D::drawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void VulkanRenderer2D::drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

	}

	void VulkanRenderer2D::drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture)
	{

	}

	void VulkanRenderer2D::flushImplementation()
	{

	}

}