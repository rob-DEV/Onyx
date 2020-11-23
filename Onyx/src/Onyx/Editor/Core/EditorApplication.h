#ifndef _ONYX_EDITOR_APPLICATION_H_
#define _ONYX_EDITOR_APPLICATION_H_

#include <Onyx/Core/Application.h>

namespace Onyx {

	class Window;
	class SceneEditor;
	class EditorInput;

	class ONYX_API EditorApplication : public Application
	{
	public:
		EditorApplication();
		~EditorApplication();

		void InitEngineComponents(SceneEditor* sceneEditor);

		void OnUpdate();

		RenderedPixelData GetRenderedFrame();
		bool* GetInputKeyBuffer();
		bool* GetInputMouseButtonBuffer();
		void SetMousePosition(float x, float y);

	private:

		EditorInput* m_EditorToEngineInput;
		SceneEditor* m_SceneEditor = nullptr;

		//ABSTRACT OUT SOMEWHERE ELSE
		char* m_FrameBufferDataPointer = nullptr;

	};

}

#endif // !_ONYX_EDITOR_APPLICATION_H_