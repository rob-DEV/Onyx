#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>
#include <Onyx/Graphics/PerspectiveCameraController.h>

#include <Onyx/Entity/Entity.h>
#include <Onyx/Entity/Registry.h>

namespace Onyx {

	class Mesh;
	class Entity;

	class ONYX_API Scene {
	public:
		Scene();
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);
		
	private:
		Registry m_EntityRegistry;

		//TESTING
		PerspectiveCameraController m_CameraController;
		Mesh* m_Mesh = nullptr;

		friend class Entity;

	};
}

#endif