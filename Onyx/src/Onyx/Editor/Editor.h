#ifndef _ONYX_EDITOR_H_
#define _ONYX_EDITOR_H_

#include <Onyx/Core/TimeStep.h>
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
		bool* GetInputMouseButtonBuffer();
		void SetMousePosition(float x, float y);

	private:
		Window* m_Window;
		EditorInput* m_EditorToEngineInput;
		Timestep m_EditorTimestep = 0;

		Scene* m_EditorScene;
		static Editor* s_EditorInstance;

		//ABSTRACT OUT SOMEWHERE ELSE
		char* frameBufferDataPointer = nullptr;

	};

}

#endif