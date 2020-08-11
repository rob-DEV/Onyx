#ifndef _ONYX_GRAPHICS_RENDERER2D_H_
#define _ONYX_GRAPHICS_RENDERER2D_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/OrthographicCamera.h>
#include <Onyx/Graphics/Texture.h>

#define RENDERER2D_MAX_VERTEX 600000

namespace Onyx {


	class ONYX_API Renderer2D {
	public:	

		//GLOBAL INITIALIZATION OF RENDERER 2D depending on which RendererAPI is in use
		static void init();
		inline static void destroy() { s_Instance->destroyImplementation(); delete s_Instance; };

		inline static void beginScene(const OrthographicCamera& camera) { s_Instance->beginSceneImplementation(camera); };
		inline static void endScene() { s_Instance->endSceneImplementation(); };

		inline static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) { s_Instance->drawQuadImplementation(position, size, color); };
		inline static void drawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture) { s_Instance->drawQuadImplementation(position, size, texture); };

		inline static void drawRotatedQuad(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color) { s_Instance->drawRotatedQuadImplementation(position, angle, ax, size, color); };
		inline static void drawRotatedQuad(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, Texture2D* texture) { s_Instance->drawRotatedQuadImplementation(position, angle, ax, size, texture); };



		inline static void flush() { s_Instance->flushImplementation(); };
	protected:

		virtual void initImplementation() = 0;
		virtual void destroyImplementation() = 0;

		virtual void beginSceneImplementation(const OrthographicCamera& camera) = 0;
		virtual void endSceneImplementation() = 0;

		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void drawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture) = 0;

		virtual void drawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void drawRotatedQuadImplementation(const glm::vec3 & position, float angle, const glm::vec3 & ax, const glm::vec2 & size, Texture2D * texture) = 0;

		virtual void flushImplementation() = 0;

	private:
		static Renderer2D* s_Instance;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_