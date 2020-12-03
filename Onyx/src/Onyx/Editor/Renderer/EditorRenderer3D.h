#ifndef _ONYX_EDITOR_RENDERER_3D_H_
#define _ONYX_EDITOR_RENDERER_3D_H_

#include <Onyx/Camera/Camera.h>
#include <Onyx/Renderer/StaticBatch.h>

namespace Onyx {
	
	class Scene;
	class Model;
	class Framebuffer;

	class EditorRenderer3D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void DrawScene(const Scene* scene);
		static void EndScene();

	private:

		static glm::mat4 m_View;
		static glm::mat4 m_WorldViewProjection;
		static Framebuffer* m_Framebuffer;

		inline static StaticBatch m_StaticBatch;


	};
}

#endif // !_ONYX_EDITOR_RENDERER_3D_H_
