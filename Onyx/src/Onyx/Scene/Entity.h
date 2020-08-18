#ifndef _ONYX_SCENE_ENTITY_H_
#define _ONYX_SCENE_ENTITY_H_

#include <Onyx/Core/Core.h>
#include <Onyx/ECS//EntityRegistry.h>

#include "Components.h"
#include "Scene.h"

namespace Onyx {

	class Scene;

	class ONYX_API Entity {
	public:
		Entity();
		Entity(ECSEntity entity, Scene* scene);	
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&& ... args) {

			//Add component to the entity ID in ECS
			return m_Scene->m_ECSEntityRegistry.AddComponent<T>(m_EntityID, std::forward<Args>(args)...);

		}

		template<typename T>
		T& GetComponent() {

			//Get component from ECS registry
			return m_Scene->m_ECSEntityRegistry.GetComponent<T>(m_EntityID);

		}

		template<typename T>
		void RemoveComponent() {
			
			//Remove component from ECS registry
			return m_Scene->m_ECSEntityRegistry.RemoveComponent<T>(m_EntityID);

		}


	private:
		ECSEntity m_EntityID;
		Scene* m_Scene = nullptr;

	};

}

#endif