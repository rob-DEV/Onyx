#include "onyxpch.h"
#include "Entity.h"
#include "Scene.h"

namespace Onyx {

	Entity::Entity() 
	{
		m_EntityID = 0xFFFFFFFF;
		m_Scene = nullptr;
	}

	Entity::Entity(ECSEntity entity, Scene* scene)
		: m_EntityID(entity), m_Scene(scene)
	{

	}

	Entity::~Entity()
	{
		printf("Destroying Entity\n");
	}

}