#include "onyxpch.h"
#include "Scene.h"

#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Editor/Gizmo.h>

#include <entt/entt.hpp>

#include <glad/glad.h>

namespace Onyx {

	Scene::Scene()
	{


	}

	Scene::~Scene()
	{
		for (auto a : m_Entities) {
			delete a;
		}

		m_Entities.clear();

	}

	Entity* Scene::CreateEntity() {

		Entity* e = new Entity(m_EntityRegistry.Create(), this);
		m_Entities.push_back(e);
		return e;
	}

	void Scene::OnUpdate(Timestep timestep)
	{

	}

}