#include "onyxpch.h"
#include "Scene.h"

#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Editor/Components/Gizmo.h>

#include <Onyx/Resources/Hasher.h>

#include <entt/entt.hpp>

#include <glad/glad.h>
#include <inttypes.h>

namespace Onyx {

	Scene::Scene() :
		m_SceneData(SceneData("Untitled", "UNSAVED", Hasher::GenerateUniqueID())),
		m_SkyBox(new Skybox(std::vector<std::string> {
			"res/textures/skybox/Left.png",
			"res/textures/skybox/Right.png",
			"res/textures/skybox/Up.png",
			"res/textures/skybox/Down.png",
			"res/textures/skybox/Front.png",
			"res/textures/skybox/Back.png"
		}))
	{

	}

	Scene::Scene(const SceneData& sceneData) :
		m_SceneData(sceneData),
		m_SkyBox(new Skybox(std::vector<std::string> {
		"res/textures/skybox/Left.png",
		"res/textures/skybox/Right.png",
		"res/textures/skybox/Up.png",
		"res/textures/skybox/Down.png",
		"res/textures/skybox/Front.png",
		"res/textures/skybox/Back.png"
	}))
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