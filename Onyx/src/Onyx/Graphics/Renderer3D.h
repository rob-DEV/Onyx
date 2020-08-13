#ifndef _ONYX_GRAPHICS_RENDERER3D_H_
#define _ONYX_GRAPHICS_RENDERER3D_H_

#include <Onyx/core/Core.h>
#include <Onyx/Graphics/OrthographicCamera.h>
#include <Onyx/Graphics/Texture.h>

namespace Onyx {

	class Mesh {

		//vertices
		//indices
		//normals
		//material
		//shader?

		//color

	};


	class ONYX_API Renderer3D {
	public:	

		//GLOBAL INITIALIZATION OF RENDERER 2D depending on which RendererAPI is in use
		static void Init();
		inline static void Destroy() { s_Instance->DestroyImplementation(); delete s_Instance; };

		inline static void BeginScene(const OrthographicCamera& camera) { s_Instance->BeginSceneImplementation(camera); };
		inline static void EndScene() { s_Instance->EndSceneImplementation(); };

		inline static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color) { s_Instance->DrawCubeImplementation(position, size, color); };

		inline static void Flush() { s_Instance->FlushImplementation(); };
	protected:

		virtual void InitImplementation() = 0;
		virtual void DestroyImplementation() = 0;

		virtual void BeginSceneImplementation(const OrthographicCamera& camera) = 0;
		virtual void EndSceneImplementation() = 0;

		virtual void DrawCubeImplementation(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color) = 0;


		virtual void FlushImplementation() = 0;

	private:
		static Renderer3D* s_Instance;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_