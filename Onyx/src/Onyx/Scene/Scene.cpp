#include "onyxpch.h"
#include "Scene.h"
#include "Entity.h"

namespace Onyx {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity() {
		Entity e(m_ECSEntityRegistry.Create(), this);
		return e;
	}

	void Scene::OnUpdate(Timestep timestep)
	{

	}

}
