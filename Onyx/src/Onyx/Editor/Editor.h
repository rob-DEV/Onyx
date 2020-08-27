#ifndef _ONYX_EDITOR_H_
#define _ONYX_EDITOR_H_

#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Window.h>

#include <glm/glm.hpp>

namespace Onyx {

	class Window;
	class Scene;
	class Model;

	class ONYX_API Editor
	{
	public:
		Editor();
		~Editor();

		void OnUpdate();
		RenderedPixelData GetRenderedFrame();
		void OnDetach();
		void CreateEntity(glm::vec3 position);

	private:
		Window* m_Window;
		Scene* m_EditorScene;
		static Editor* s_EditorInstance;

		Model* m_ModelTest;

	};

}

#endif