#ifndef _ONYX_RENDERER_3D_H_
#define _ONYX_RENDERER_3D_H_

#include <Onyx/Camera/Camera.h>
#include "StaticBatch.h"

namespace Onyx {

	class Scene;
	class Model;

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void DrawSkybox(const Scene* scene);
		static void DrawScene(const Scene* scene);
		static void EndScene();

	private:

		static glm::mat4 m_View;
		static glm::mat4 m_WorldViewProjection;

		inline static StaticBatch m_StaticBatch;
	};

}

#endif // !_ONYX_RENDERER_3D_H_