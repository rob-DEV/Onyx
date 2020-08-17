#ifndef _ONYX_SCENE_H_
#define _ONYX_SCENE_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

#include <Onyx/ECS/EntityRegistry.h>

namespace Onyx {

	class Entity;

	class ONYX_API Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity();

		void OnUpdate(Timestep timestep);

	private:
		ECSEntityRegistry m_ECSEntityRegistry;

		friend class Entity;

	};
}

#endif