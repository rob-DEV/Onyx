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
		m_ModelTest(ModelLoader::LoadFromFile("res/models/Scene.obj")),
		m_GizmoTest(new Gizmo())
	{


	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity() {
		return new Entity(m_EntityRegistry.Create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		static FirstPersonCameraController cam = FirstPersonCameraController();
		cam.OnUpdate(timestep);

		m_Camera = cam.GetCamera();

		static float rotation = 0;
		rotation += 0.09f;

		RenderCommand::SetClearColour(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();


		Renderer3D::BeginScene(cam.GetCamera());

		Renderer3D::DrawScene(this);


		for (int i = 0; i < m_ModelTest->m_Meshes.size(); ++i) {
			Renderer3D::DrawMesh(m_ModelTest->m_Meshes[i], glm::vec3(25.0f, rotation / 2.0f, 0.0f), glm::vec3(1.0f));
		}

		for (int i = 0; i < m_GizmoTest->m_TransformModel->m_Meshes.size(); ++i) {
			Renderer3D::DrawRotatedMesh(m_GizmoTest->m_TransformModel->m_Meshes[i], rotation, glm::vec3(0,1,0), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f));
		}

		Renderer3D::EndScene();
		Renderer3D::Flush();
		
	}

}