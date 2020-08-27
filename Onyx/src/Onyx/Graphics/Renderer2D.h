#ifndef _ONYX_GRAPHICS_RENDERER2D_H_
#define _ONYX_GRAPHICS_RENDERER2D_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Camera/OrthographicCamera.h>
#include <Onyx/Graphics/Texture.h>

namespace Onyx {


	class ONYX_API Renderer2D {
	public:	

		//GLOBAL INITIALIZATION OF RENDERER 2D depending on which RendererAPI is in use
		static void Init();
		inline static void Destroy() { s_Instance->DestroyImplementation(); delete s_Instance; };

		inline static void BeginScene(const OrthographicCamera& camera) { s_Instance->BeginSceneImplementation(camera); };
		inline static void EndScene() { s_Instance->EndSceneImplementation(); };

		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) { s_Instance->DrawQuadImplementation(position, size, color); };
		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture) { s_Instance->DrawQuadImplementation(position, size, texture); };

		inline static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color) { s_Instance->DrawRotatedQuadImplementation(position, angle, ax, size, color); };
		inline static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, Texture2D* texture) { s_Instance->DrawRotatedQuadImplementation(position, angle, ax, size, texture); };



		inline static void Flush() { s_Instance->FlushImplementation(); };
	protected:

		virtual void InitImplementation() = 0;
		virtual void DestroyImplementation() = 0;

		virtual void BeginSceneImplementation(const OrthographicCamera& camera) = 0;
		virtual void EndSceneImplementation() = 0;

		virtual void DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void DrawQuadImplementation(const glm::vec3& position, const glm::vec2& size, Texture2D* texture) = 0;

		virtual void DrawRotatedQuadImplementation(const glm::vec3& position, float angle, const glm::vec3& ax, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void DrawRotatedQuadImplementation(const glm::vec3 & position, float angle, const glm::vec3 & ax, const glm::vec2 & size, Texture2D * texture) = 0;

		virtual void FlushImplementation() = 0;

	private:
		static Renderer2D* s_Instance;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_