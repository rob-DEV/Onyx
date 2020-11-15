#ifndef _ONYX_EDITOR_SCENE_H_
#define _ONYX_EDITOR_SCENE_H_

#include <Onyx/Core/Core.h>

namespace Onyx {

	class FirstPersonCameraController;
	class Entity;

	class ONYX_API EditorScene {

		EditorScene();
		~EditorScene();

		std::vector<Entity*> m_EditorSceneEntities;
		FirstPersonCameraController* m_EditorSceneCamera;

	};

}


#endif