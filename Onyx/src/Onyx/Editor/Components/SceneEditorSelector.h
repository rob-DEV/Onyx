#ifndef _ONYX_SCENE_EDITOR_SELECTOR_H_
#define _ONYX_SCENE_EDITOR_SELECTOR_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Camera/FirstPersonCameraController.h>

namespace Onyx {
	
	class Mesh;

	class ONYX_API SceneEditorSelector
	{
	public:

		SceneEditorSelector(FirstPersonCameraController* editorCamera);
		void OnUpdate();

	private:
		FirstPersonCameraController* m_EditorCamera;
	};
}

#endif // !_ONYX_SCENE_EDITOR_SELECTOR_H_
