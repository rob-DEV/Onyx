#ifndef _ONYX_EDITOR_APPLICATION_H_
#define _ONYX_EDITOR_APPLICATION_H_

#include <Onyx/Core/Application.h>

namespace Onyx {

	class Window;
	class SceneEditor;
	class EditorInput;
	class SceneEditorViewport;

	class ONYX_API EditorApplication : public Application
	{
	public:
		EditorApplication();
		~EditorApplication();

		void InitEngineComponents(SceneEditor* sceneEditor);

		void OnUpdate();

		void GetRenderedFrame(int* buffer);
		bool* GetInputKeyBuffer();
		bool* GetInputMouseButtonBuffer();
		void SetMousePosition(float x, float y);

	private:

		EditorInput* m_EditorToEngineInput;
		SceneEditorViewport* m_EditorRenderer;
		SceneEditor* m_SceneEditor;
	};

}

#endif // !_ONYX_EDITOR_APPLICATION_H_