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

	void VulkanRenderer2D::InitImplementation()
	{
		
	}

	void VulkanRenderer2D::DestroyImplementation()
	{

	}

	void VulkanRenderer2D::BeginSceneImplementation(const OrthographicCamera& camera)
	{
		VulkanSwapchain::Get()->SetViewMatrixTest(camera.GetViewProjectionMatrix());
	}

	void VulkanRenderer2D::EndSceneImplementation()
	{

	}

	void VulkanRenderer2D::DrawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void VulkanRenderer2D::DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

	}

	void VulkanRenderer2D::DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture)
	{

	}

	void VulkanRenderer2D::DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color)
	{

	}

	void VulkanRenderer2D::DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, Texture2D* texture)
	{

	}

	void VulkanRenderer2D::FlushImplementation()
	{
		VulkanSwapchain::Get()->DrawFrame();
	}

}