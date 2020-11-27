#include "onyxpch.h"
#include "Entity.h"

#include <entt/entt.hpp>
#include <Onyx/Scene/Scene.h>

#define ADD_COMPONENT_IMPL(comp) template <> comp& Entity::AddComponent<comp>(comp& component) { \
	void* reg = m_Scene->m_EntityRegistry.m_Registry; \
	return ((entt::registry*)(reg))->emplace<comp>((entt::entity)m_EntityID, component); \
} \

#define HAS_COMPONENT_IMPL(comp) template <> bool Entity::HasComponent<comp>() { \
	void* reg = m_Scene->m_EntityRegistry.m_Registry; \
	return ((entt::registry*)(reg))->has<comp>((entt::entity)m_EntityID); \
} \

#define GET_COMPONENT_IMPL(comp) template <> comp& Entity::GetComponent<comp>() { \
	void* reg = m_Scene->m_EntityRegistry.m_Registry;\
	return ((entt::registry*)(reg))->get<comp>((entt::entity)m_EntityID);\
} \

namespace Onyx {

	Entity::Entity(uint32_t entity, Scene* scene) : m_EntityID(entity), m_Scene(scene)
	{

	}

	Entity::~Entity()
	{
		void* reg = m_Scene->m_EntityRegistry.m_Registry;
		((entt::registry*)(reg))->destroy((entt::entity)m_EntityID); \
	}

	//ADD
	ADD_COMPONENT_IMPL(TagComponent);
	ADD_COMPONENT_IMPL(TransformComponent);
	ADD_COMPONENT_IMPL(MeshRendererComponent);


	//HAS
	HAS_COMPONENT_IMPL(TagComponent);
	HAS_COMPONENT_IMPL(TransformComponent);
	HAS_COMPONENT_IMPL(MeshRendererComponent);

	//GET
	GET_COMPONENT_IMPL(TagComponent);
	GET_COMPONENT_IMPL(TransformComponent);
	GET_COMPONENT_IMPL(MeshRendererComponent);

}
