#ifndef _ONYX_GRAPHICS_RENDERER2D_H_
#define _ONYX_GRAPHICS_RENDERER2D_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/OrthographicCamera.h>
#include <Onyx/Graphics/Texture.h>

namespace Onyx {

	struct Vertex2D {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};

	class ONYX_API Renderer2D {
	public:	

		//GLOBAL INITIALIZATION OF RENDERER 2D depending on which RendererAPI is in use
		static void init();
		inline static void destroy() { s_Instance->destroyImplementation(); delete s_Instance; };

		inline static void beginScene(const OrthographicCamera& camera) { s_Instance->beginSceneImplementation(camera); };
		inline static void endScene() { s_Instance->endSceneImplementation(); };

		inline static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) { s_Instance->drawQuadImplementation(position, size, color); };
		inline static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) { s_Instance->drawQuadImplementation(position, size, color); };
		inline static void drawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture) { s_Instance->drawQuadImplementation(position, size, texture); };

	protected:

		virtual void initImplementation() = 0;
		virtual void destroyImplementation() = 0;

		virtual void beginSceneImplementation(const OrthographicCamera& camera) = 0;
		virtual void endSceneImplementation() = 0;

		virtual void drawQuadImplementation(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture) = 0;

	private:
		static Renderer2D* s_Instance;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_