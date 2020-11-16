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

	class ONYX_API Editor
	{
	public:
		Editor();
		~Editor();

		void OnUpdate();
		RenderedPixelData GetRenderedFrame();

		void OnDetach();

		bool* GetInputKeyBuffer();
		bool* GetInputMouseButtonBuffer();
		void SetMousePosition(float x, float y);

		SceneEditor* m_SceneEditor;

	private:
		Window* m_Window;
		EditorInput* m_EditorToEngineInput;
		Timestep m_EditorTimestep = 0;

		static Editor* s_EditorInstance;

		//ABSTRACT OUT SOMEWHERE ELSE
		char* m_FrameBufferDataPointer = nullptr;

	};

}

#endif