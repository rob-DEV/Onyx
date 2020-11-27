#ifndef _ONYX_EDITOR_SCENE_H_
#define _ONYX_EDITOR_SCENE_H_

#include <Onyx/Core/Core.h>

#include <Onyx/Core/TimeStep.h>

#include <vector>

namespace Onyx {

	class EditorCameraController;
	class Gizmo;
	class Scene;
	class Entity;
	class SceneEditorSelector;

	class ONYX_API SceneEditor {
	public:
		SceneEditor();
		~SceneEditor();

		void OnUpdate(Timestep ts);

		bool NewScene();
		bool OpenScene(const char* filePath);
		bool SaveScene(const char* filePath);

		std::vector<Entity*> GetAllEntitiesTest();
		void SetSelectedEntity(uint32_t id);

	private:
		void InvalidateScene();

		//Initialize First
		EditorCameraController* m_EditorCameraController;
		
		Scene* m_Scene;
		Entity* m_SelectedEntity;

		SceneEditorSelector* m_SceneSelector;

		Gizmo* m_EditorGizmo;

		friend class EditorCore;
		friend class SceneEditorSelector;

	};

}


#endif // !_ONYX_EDITOR_SCENE_H_