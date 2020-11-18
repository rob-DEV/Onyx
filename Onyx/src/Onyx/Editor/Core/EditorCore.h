#ifndef _ONYX_EDITOR_H_
#define _ONYX_EDITOR_H_

#include <Onyx/Core/TimeStep.h>
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Core/Window.h>


#include <glm/glm.hpp>

namespace Onyx {

	class Window;
	class SceneEditor;
	class EditorInput;

	class ONYX_API EditorCore
	{
	public:
		EditorCore();
		~EditorCore();

		void InitEngineComponents(SceneEditor* sceneEditor);

		void OnUpdate();
		RenderedPixelData GetRenderedFrame();

		void OnDetach();

		bool* GetInputKeyBuffer();
		bool* GetInputMouseButtonBuffer();
		void SetMousePosition(float x, float y);


	private:
		Window* m_Window;
		EditorInput* m_EditorToEngineInput;
		Timestep m_EditorTimestep = 0;

		SceneEditor* m_SceneEditor = nullptr;

		//ABSTRACT OUT SOMEWHERE ELSE
		char* m_FrameBufferDataPointer = nullptr;

	};

}

#endif