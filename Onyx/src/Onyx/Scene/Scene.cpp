#include "onyxpch.h"
#include "Scene.h"

#include <Onyx/Core/Input.h>
#include <Onyx/Graphics/Renderer3D.h>

namespace Onyx {

	Scene::Scene()
	{
		m_CameraController = PerspectiveCameraController();
		m_Mesh = Mesh::Create(PrimitiveMeshType::Cube);

		Entity* ENT = CreateEntity();

		TransformComponent a = TransformComponent();
		a.Position = glm::vec3(10.0f);
		ENT->AddComponent<TransformComponent>(a);


		TransformComponent& g = ENT->GetComponent<TransformComponent>();


	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity() {
		return new Entity(m_EntityRegistry.Create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		//2D

		//3D
		static const PerspectiveCamera& camera = m_CameraController.GetCamera();
		m_CameraController.OnUpdate(timestep);

		Renderer3D::BeginScene(camera);

		//auto view = m_EntityRegistry.view<TransformComponent, MeshRendererComponent>();

		//Mouse interaction (editor)
		std::pair<float, float> normalizedMouseInput = Input::GetMousePositionNormalized();

		Ray ray = camera.ScreenPointToRay();
		glm::vec3 pointOnRay = ray.GetPoint(10.0f);

		printf("RAY: %.3f, %.3f, %.3f\n", pointOnRay.x, pointOnRay.y, pointOnRay.z);

		Ray rayWorld = Ray(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 1.0f));

		for (float i = 0; i < 200; i += 0.5f) {

			glm::vec3 point = rayWorld.GetPoint(i);
			Renderer3D::DrawMesh(m_Mesh, point, glm::vec3(0.5f));
		}



		Renderer3D::DrawMesh(m_Mesh, pointOnRay, glm::vec3(0.5f));

// 		for (auto entity : view)
// 		{
// 			auto [transform, meshRenderer] = view.get<TransformComponent, MeshRendererComponent>(entity);
// 
// 			glm::vec3 position = transform.Position;
// 
// 			//assuming scale is uniform
// 			//if (abs(glm::distance(position, pointonray)) < transform.Scale.x - .35f) {
// 				//meshRenderer.GetMesh()->Select(true);
// 			//}
// 			//else {
// 				//meshRenderer.GetMesh()->Select(false);
// 			//}
// 
// 			Renderer3D::DrawMesh(meshRenderer.GetMesh(), transform.Position, transform.Scale);
// 
// 
// 		}

		Renderer3D::EndScene();
		Renderer3D::Flush();


	}

}