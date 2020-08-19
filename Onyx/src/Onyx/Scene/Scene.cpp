#include "onyxpch.h"
#include "Scene.h"
#include "Entity.h"
#include <Onyx/Graphics/Renderer3D.h>

namespace Onyx {

	Scene::Scene()
	{
		m_CameraController = PerspectiveCameraController();
		m_Mesh = Mesh::Create(PrimitiveMeshType::Cube);

		for (int i=0; i < 100; ++i)
		{
			Entity* e = CreateEntity();
			e->AddComponent<TransformComponent>(TransformComponent(glm::vec3(i,i,0.0f)));
			e->AddComponent<MeshRendererComponent>(MeshRendererComponent(m_Mesh));


		}


	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity() {
		return new Entity(m_EntityRegistry.create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{

		//2D

		//3D
		static const PerspectiveCamera& camera = m_CameraController.GetCamera();
		m_CameraController.OnUpdate(timestep);

		Renderer3D::BeginScene(camera);
		
		auto view = m_EntityRegistry.view<TransformComponent, MeshRendererComponent>();

		for (auto entity : view)
		{
			auto [transform, meshRenderer] = view.get<TransformComponent, MeshRendererComponent>(entity);

			Renderer3D::DrawMesh(meshRenderer.GetMesh(),transform.GetLocalPosition(), transform.GetScale());


		}

		//Renderer3D::DrawMesh(m_Mesh, glm::vec3(0.0f), glm::vec3(10.0f));
 		

		Renderer3D::EndScene();
		Renderer3D::Flush();


	}

}
