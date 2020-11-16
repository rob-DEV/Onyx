#ifndef _ONYX_EDITOR_SCENE_H_
#define _ONYX_EDITOR_SCENE_H_

#include <Onyx/Core/Core.h>

#include <Onyx/Core/TimeStep.h>

namespace Onyx {

	class FirstPersonCameraController;
	class Gizmo;
	class Scene;

	class ONYX_API SceneEditor {
	public:
		SceneEditor();
		~SceneEditor();

		void OnUpdate(Timestep ts);

		bool OpenScene(const char* filePath);
		bool SaveScene(const char* filePath);

	private:
		Scene* m_Scene;

		Gizmo* m_EditorGizmo;
		FirstPersonCameraController* m_EditorCamera;
	
		friend class Editor;

	};

}


#endif // !_ONYX_EDITOR_SCENE_H_