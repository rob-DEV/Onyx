#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>
#include <Onyx/Camera/FirstPersonCameraController.h>

#include <Onyx/Graphics/Skybox.h>

#include <Onyx/Entity/Entity.h>
#include <Onyx/Entity/Registry.h>

namespace Onyx {

	class Entity;
	class Model;
	class Gizmo;
	

	class ONYX_API Scene {
	public:
		Scene();
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);

	private:
		Registry m_EntityRegistry;

		//ENTITIES
		std::vector<Entity*> m_Entities;

		friend class Entity;
		friend class SceneEditor;
		friend class SceneSerializer;
		friend class EditorRenderer;
		friend class OpenGLRenderer3D;
	};
}

#endif