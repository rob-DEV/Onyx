#ifndef _ONYX_EDITOR_H_
#define _ONYX_EDITOR_H_

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Window.h>



namespace Onyx {

	class Window;
	class PerspectiveCamera;
	class PerspectiveCameraController;
	class Mesh;

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
		PerspectiveCamera* m_EditorCamera;
		Mesh* m_Mesh;
		static Editor* s_EditorInstance;
		float m_Rotation = 0.0f;

	};

}

#endif