#ifndef _ONYX_EDITOR_RENDERER_H_
#define _ONYX_EDITOR_RENDERER_H_

#include <Onyx/core/Core.h>
#include <Onyx/Camera/Camera.h>
#include <Onyx/Graphics/Texture.h>
#include <Onyx/Graphics/Mesh.h>


namespace Onyx {
	class Scene;
	class Gizmo;

	class ONYX_API EditorRenderer {
	public:	

		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Flush();


		static void DrawScene(const Scene* scene);
		static void DrawGizmo(const Gizmo* gizmo);

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_