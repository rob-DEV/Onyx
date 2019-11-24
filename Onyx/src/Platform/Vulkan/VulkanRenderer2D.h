#ifndef _ONYX_PLATFORM_VULKAN_RENDERER2D_H_
#define _ONYX_PLATFORM_VULKAN_RENDERER2D_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/Renderer2D.h>


#include <glm/glm.hpp>

namespace Onyx {

	class VulkanRenderer2D : public Renderer2D {
		virtual void initImplementation();
		virtual void destroyImplementation();

		virtual void beginSceneImplementation(const OrthographicCamera& camera);
		virtual void endSceneImplementation();

		virtual void drawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture);
		virtual void flushImplementation();
	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_