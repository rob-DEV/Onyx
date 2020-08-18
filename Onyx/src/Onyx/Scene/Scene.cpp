#include "onyxpch.h"
#include "Scene.h"
#include "Entity.h"
#include <Onyx/Graphics/Renderer3D.h>

namespace Onyx {

	Scene::Scene()
	{
		m_CameraController = PerspectiveCameraController();

		Mesh* mesh = Mesh::Create(PrimitiveMeshType::Cone);

		for (int i = 0; i < 10000; ++i)
		{
			Entity* ent = CreateEntity();
			ent->AddComponent<TransformComponent>(glm::vec3(2.0f));


			m_Entities.push_back(ent);
		}


		
	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity() {
		return new Entity(m_ECSEntityRegistry.Create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{

		//2D


		//3D
		static const PerspectiveCamera& camera = m_CameraController.GetCamera();
		//m_CameraController.OnUpdate(timestep);

		//Renderer3D::BeginScene(camera);

		ECSView<TransformComponent> transformView = m_ECSEntityRegistry.View<TransformComponent>();
		//ECSView<MeshRendererComponent> meshRendererView = m_ECSEntityRegistry.View<MeshRendererComponent>();

		Tuple<int, float> ff = Tuple<int, float>(1, 22.0f);

		printf("%d\n", get<0>(ff));


		//API sketching
		//m.Get<TransformComponent, MeshRendererComponent>(0).push_back(std::move(TransformComponent()));

		//printf("%d", m.access<TransformComponent>(0).size());
		//auto& [transform, mesh] = complexTemporary.v[0];


		//printf("%.4f", transform.GetLocalPosition().x);


		//View<int, float> simple(55, 3.0f);


		//View<TransformComponent, MeshRendererComponent> mRenderView = View<TransformComponent, MeshRendererComponent>(transform, mesh);
		

		//auto& [transform, mesh] = mRenderView.Data;

		


// 		for (int i = 0; i < meshRendererView.size; ++i)
// 		{
// 			Renderer3D::DrawMesh(meshRendererView.data[i].GetMesh(), { i, i, 0.0f }, { 0.8f,0.8f ,0.8f });
// 		}

		//Renderer3D::EndScene();
		//Renderer3D::Flush();


	}

}
