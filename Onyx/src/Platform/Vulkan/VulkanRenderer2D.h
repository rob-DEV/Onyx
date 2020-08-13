#ifndef _ONYX_PLATFORM_VULKAN_RENDERER2D_H_
#define _ONYX_PLATFORM_VULKAN_RENDERER2D_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/Renderer2D.h>


#include "VulkanDevice.h"
#include "VulkanBuffer.h"
#include "VulkanSwapchain.h"

#include <glm/glm.hpp>

namespace Onyx {

	struct Vertex2D;

	class VulkanRenderer2D : public Renderer2D {
		
		virtual void InitImplementation();
		virtual void DestroyImplementation();

		virtual void BeginSceneImplementation(const OrthographicCamera& camera);
		virtual void EndSceneImplementation();

		virtual void DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		virtual void DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture);

		virtual void DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color);
		virtual void DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, Texture2D* texture);


		virtual void FlushImplementation();

	private:		
		Vertex2D* m_QuadVertexBufferData;
		Vertex2D* m_QuadVertexBufferDataPtr;

		VulkanSwapchain* m_Swapchain;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_