#ifndef _ONYX_ENTITY_H_
#define _ONYX_ENTITY_H_

#include <Onyx/Core/Core.h>

#include "Components.h"

namespace Onyx {

	class Scene;

	class ONYX_API Entity {
	public:

		Entity(uint32_t entity, Scene* scene);
		~Entity();

		//ADD COMPONENTS CAN'T USE TEMPLATING ATM DUE TO CLR
		template<typename T, typename... Args>
		T& AddComponent(Args& ... args);

		template <> TransformComponent& AddComponent<TransformComponent>(TransformComponent& component);
		template <> MeshRendererComponent& AddComponent<MeshRendererComponent>(MeshRendererComponent& component);


		template<typename T>
		T& GetComponent();


		
	private:
		
		uint32_t m_EntityID;
		Scene* m_Scene = nullptr;
	};

}

#endif