#include "onyxpch.h"
#include "Scene.h"

#include <Onyx/Graphics/Renderer3D.h>
#include <Platform/Windows/WindowsInput.h>
#include <entt/entt.hpp>

namespace Onyx {

	Scene::Scene()
	{
		m_CameraController = PerspectiveCameraController();


	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity() {
		return new Entity(m_EntityRegistry.Create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		timestep = Timestep(10.0f);
		//2D

		//3D
		//static const PerspectiveCamera& camera = m_CameraController.GetCamera();
		//m_CameraController.OnUpdate(timestep);

		static float rotation = 0;
		rotation += 1.0f;


		Renderer3D::BeginScene(m_CameraController.GetCamera());


		//Mouse interaction (editor)

		//Ray ray = camera.ScreenPointToRay();
		//glm::vec3 pointOnRay = ray.GetPoint(10.0f);

		//printf("RAY: %.3f, %.3f, %.3f\n", pointOnRay.x, pointOnRay.y, pointOnRay.z);

		//Ray rayWorld = Ray(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 1.0f));

		//for (float i = 0; i < 200; i += 0.5f) {

		//	glm::vec3 point = rayWorld.GetPoint(i);
			//Renderer3D::DrawMesh(m_Mesh, point, glm::vec3(0.5f));
	//	}

		auto view = ((entt::registry*)(m_EntityRegistry.m_Registry))->view<TransformComponent, MeshRendererComponent>();


		//Renderer3D::DrawMesh(m_Mesh, glm::vec3(0.0f), glm::vec3(10.0f));

		for (auto entity : view)
		{
			auto [transform, meshRenderer] = view.get<TransformComponent, MeshRendererComponent>(entity);

			glm::vec3 position = transform.Position;

			Renderer3D::DrawRotatedMesh(meshRenderer.GetMesh(), rotation, glm::vec3(0,1,0), transform.Position, transform.Scale * glm::vec3(3.0f));

		}

		Renderer3D::EndScene();
		Renderer3D::Flush();


	}

}