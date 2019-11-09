#ifndef _ONYX_GRAPHICS_RENDERER2D_H_
#define _ONYX_GRAPHICS_RENDERER2D_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/OrthographicCamera.h>
#include <Onyx/Graphics/Texture.h>


#include <glm/glm.hpp>

namespace Onyx {

	class ONYX_API Renderer2D {
	public:
	
		static void init();
		static void destroy();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture);


	private:

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_