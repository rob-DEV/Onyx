#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>
#include <Onyx/Graphics/PerspectiveCameraController.h>

#include <entt/entt.hpp>

namespace Onyx {

	class Mesh;
	class Entity;

	class ONYX_API Scene {
	public:
		Scene();
		~Scene();

		Entity* CreateEntity();
		void OnUpdate(Timestep timestep);
		glm::vec3 Raycast(float mouse_x, float mouse_y);

	private:
		PerspectiveCameraController m_CameraController;
		entt::registry m_EntityRegistry;
		Mesh* m_Mesh = nullptr;

		friend class Entity;

	};
}

#endif