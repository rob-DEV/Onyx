#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>
#include <Onyx/ECS/EntityRegistry.h>
#include <Onyx/Graphics/PerspectiveCameraController.h>

#include <vector>

namespace Onyx {

	class Entity;

	class ONYX_API Scene {
	public:
		Scene();
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);

	private:
		ECSEntityRegistry m_ECSEntityRegistry;
		PerspectiveCameraController m_CameraController;

		std::vector<Entity*> m_Entities;

		friend class Entity;

	};
}

#endif