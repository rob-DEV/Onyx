#ifndef _ONYX_SCENE_ENTITY_H_
#define _ONYX_SCENE_ENTITY_H_

#include <Onyx/Core/Core.h>
#include <Onyx/ECS//EntityRegistry.h>

#include "Scene.h"
#include "Components.h"

namespace Onyx {

	class ONYX_API Entity {
	public:
		Entity() = default;
		Entity(ECSEntity entityID, Scene* scene) 
			: m_EntityID(entityID), m_Scene(scene) { };


		template<typename T, typename... Args>
		T AddComponent(Args&& ... args) {

			//add component to the entity ID in ECS
			//return m_Scene->m_ECSEntityRegistry.AddComponent(m_EntityID, std::forward<Args>(args));
			return T(args ...);
		}



	private:
		ECSEntity m_EntityID;
		Scene* m_Scene = nullptr;

	};

}

#endif