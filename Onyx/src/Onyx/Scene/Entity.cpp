#include "onyxpch.h"
#include "Entity.h"
#include "Scene.h"

namespace Onyx {

	Entity::Entity(entt::entity entity, Scene* scene)
		: m_EntityID(entity), m_Scene(scene)
	{

	}

	Entity::~Entity()
	{
		printf("Destroying Entity\n");
	}

}