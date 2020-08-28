#ifndef _ONYX_EDITOR_H_
#define _ONYX_EDITOR_H_

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Window.h>


#include <glm/glm.hpp>

namespace Onyx {

	class Window;
	class Scene;
	class EditorInput;

	class ONYX_API Editor
	{
	public:
		Editor();
		~Editor();

		void OnUpdate();
		RenderedPixelData GetRenderedFrame();
		void OnDetach();
		void CreateEntity(glm::vec3 position);

		bool* GetInputKeyBuffer();
		void SetMousePosition(float x, float y);

	private:
		Window* m_Window;
		EditorInput* m_EditorToEngineInput;

		Scene* m_EditorScene;
		static Editor* s_EditorInstance;

	};

}

#endif