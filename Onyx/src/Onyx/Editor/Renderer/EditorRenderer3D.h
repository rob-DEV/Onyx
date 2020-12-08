#ifndef _ONYX_EDITOR_RENDERER_3D_H_
#define _ONYX_EDITOR_RENDERER_3D_H_

#include <Onyx/Camera/Camera.h>
#include <Onyx/Renderer/StaticBatch.h>

namespace Onyx {
	
	class Scene;
	class Model;
	class Framebuffer;


	struct EditorRendererData {
		glm::mat4 View;
		glm::mat4 WorldViewProjection;

		Framebuffer* Framebuffer;

		uint32_t ViewportColorAttachment = 0;
		uint32_t SelectionColorAttachment = 0;

		StaticBatch StaticBatch;

		uint32_t SelectionPixelBuffers[2];
		uint32_t PboIndex = 0;
		uint32_t PboNextIndex = 0;

		VertexArray* ScreenQuadVAO;
		VertexBuffer* ScreenQuadVBO;
		Shader* ScreenShader;

	};

	class EditorRenderer3D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void DrawScene(const Scene* scene);
		static void EndScene();

	private:

		static EditorRendererData s_RendererData;

	};
}

#endif // !_ONYX_EDITOR_RENDERER_3D_H_
