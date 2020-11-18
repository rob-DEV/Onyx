#ifndef _ONYX_ENTITY_H_
#define _ONYX_ENTITY_H_

#include <Onyx/Core/Core.h>

#include "Components.h"

#define ADD_COMPONENT(comp) template <> comp& AddComponent<comp>(comp& component)
#define HAS_COMPONENT(comp) template <> bool HasComponent<comp>()
#define GET_COMPONENT(comp) template <> comp& GetComponent<comp>()




namespace Onyx {

	class Scene;

	class ONYX_API Entity {
	public:

		Entity(uint32_t entity, Scene* scene);
		~Entity();

		//TEST
		uint32_t GetID() const { return m_EntityID; }

		//ADD COMPONENTS CAN'T USE TEMPLATING ATM DUE TO CLR
		template<typename T, typename... Args>
		T& AddComponent(Args& ... args);

		//TEMPLATING MACRO
		ADD_COMPONENT(TagComponent);
		ADD_COMPONENT(TransformComponent);
		ADD_COMPONENT(MeshRendererComponent);


		template<typename T>
		bool HasComponent();

		HAS_COMPONENT(TagComponent);
		HAS_COMPONENT(TransformComponent);
		HAS_COMPONENT(MeshRendererComponent);


		template<typename T>
		T& GetComponent();
		GET_COMPONENT(TagComponent);
		GET_COMPONENT(TransformComponent);
		GET_COMPONENT(MeshRendererComponent);
		
	private:
		uint32_t m_EntityID;
		Scene* m_Scene = nullptr;
	};

}

#endif