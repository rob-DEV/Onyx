#ifndef _ONYX_SCENE_EDITOR_SELECTOR_H_
#define _ONYX_SCENE_EDITOR_SELECTOR_H_

#include <Onyx/Core/Core.h>

namespace Onyx {
	
	class SceneEditor;
	
	class ONYX_API SceneEditorSelector
	{
	public:

		SceneEditorSelector(SceneEditor* sceneEditor);
		void OnUpdate();

	private:
		SceneEditor* m_SceneEditor;
	};
}

#endif // !_ONYX_SCENE_EDITOR_SELECTOR_H_
