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
		
		const Camera& GetCamera() const { return m_Camera; }
		const Skybox& GetSkybox() const { return m_Skybox; }

	private:
		Registry m_EntityRegistry;


		//ENTITIES
		std::vector<Entity*> m_Entities;

		//TESTING
		Skybox m_Skybox;
		FirstPersonPerspectiveCamera m_Camera;
		Model* m_ModelTest;

		friend class Entity;
		friend class SceneEditor;
		friend class SceneSerializer;
	};
}

#endif