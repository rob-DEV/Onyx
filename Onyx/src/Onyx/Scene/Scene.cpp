#include "onyxpch.h"
#include "Scene.h"

#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>

#include <entt/entt.hpp>

namespace Onyx {

	Scene::Scene() : m_CameraController(60.0f, 1.77777777f, 0.00000001, 1000000.0f)
	{
		m_ModelTest = ModelLoader::LoadFromFile("res/models/Scene.obj");
	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity() {
		return new Entity(m_EntityRegistry.Create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		timestep = Timestep(16.6f);

		static float rotation = 0;
		rotation += 1.0f;

		RenderCommand::SetClearColour(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer3D::BeginScene(m_CameraController);

		for (int i = 0; i < m_ModelTest->m_Meshes.size(); ++i) {
			Renderer3D::DrawMesh(m_ModelTest->m_Meshes[i], glm::vec3(0.0f, -4.0f, -15.0f), glm::vec3(1.0f));
		}

		Renderer3D::EndScene();
		Renderer3D::Flush();

	}

}