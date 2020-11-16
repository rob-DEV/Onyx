#include "onyxpch.h"
#include "Scene.h"

#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Editor/Gizmo.h>

#include <entt/entt.hpp>

#include <glad/glad.h>

namespace Onyx {

	Scene::Scene() :
		m_Camera(60.0f, 1.77777777f, 0.00000001, 1000000.0f), 
		m_Skybox(std::vector<std::string> 
		{
			"res/textures/skybox/Left.jpg",
			"res/textures/skybox/Right.jpg",
			"res/textures/skybox/Up.jpg",
			"res/textures/skybox/Down.jpg",
			"res/textures/skybox/Front.jpg",
			"res/textures/skybox/Back.jpg"
		}),
		m_ModelTest(ModelLoader::LoadFromFile("res/models/Scene.obj"))
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