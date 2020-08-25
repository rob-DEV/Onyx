#include "onyxpch.h"
#include "Entity.h"

#include <entt/entt.hpp>
#include <Onyx/Scene/Scene.h>

namespace Onyx {

	Entity::Entity(uint32_t entity, Scene* scene) : m_EntityID(entity), m_Scene(scene)
	{

	}

	Entity::~Entity()
	{

	}


	template <> TransformComponent& Entity::AddComponent<TransformComponent>(TransformComponent& component) {
		void* reg = m_Scene->m_EntityRegistry.m_Registry;
		return ((entt::registry*)(reg))->emplace<TransformComponent>((entt::entity)m_EntityID, component);
	}

	template <> MeshRendererComponent& Entity::AddComponent<MeshRendererComponent>(MeshRendererComponent& component) {
		void* reg = m_Scene->m_EntityRegistry.m_Registry;
		return ((entt::registry*)(reg))->emplace<MeshRendererComponent>((entt::entity)m_EntityID, component);
	}



	template <> TransformComponent& Entity::GetComponent<TransformComponent>() {
		void* reg = m_Scene->m_EntityRegistry.m_Registry;
		return ((entt::registry*)(reg))->get<TransformComponent>((entt::entity)m_EntityID);
	}

	template <> MeshRendererComponent& Entity::GetComponent<MeshRendererComponent>() {
		void* reg = m_Scene->m_EntityRegistry.m_Registry;
		return ((entt::registry*)(reg))->get<MeshRendererComponent>((entt::entity)m_EntityID);
	}

}
