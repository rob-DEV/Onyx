#ifndef _ONYX_EDITOR_H_
#define _ONYX_EDITOR_H_

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Window.h>



namespace Onyx {

	class Window;
	class PerspectiveCamera;
	class OrthographicCamera;
	class PerspectiveCameraController;
	class Mesh;
	class Texture;

	class ONYX_API Editor
	{
	public:
		Editor();
		~Editor();

		void OnUpdate();
		RenderedPixelData GetRenderedFrame();
		void OnDetach();

	private:
		Window* m_Window;

		OrthographicCamera* m_OrthoEditorCamera;
		PerspectiveCamera* m_PerspEditorCamera;

		Mesh* m_Mesh;
		Texture* m_Texture;
		static Editor* s_EditorInstance;
		float m_Rotation = 0.0f;

	};

}

#endif