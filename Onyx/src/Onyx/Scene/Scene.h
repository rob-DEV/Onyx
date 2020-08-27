#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>
#include <Onyx/Camera/FirstPersonCameraController.h>

#include <Onyx/Entity/Entity.h>
#include <Onyx/Entity/Registry.h>

namespace Onyx {

	class Entity;
	class Model;

	class ONYX_API Scene {
	public:
		Scene();
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);
		
	private:
		Registry m_EntityRegistry;

		//TESTING
		FirstPersonPerspectiveCamera m_CameraController;
		Model* m_ModelTest;

		friend class Entity;

	};
}

#endif