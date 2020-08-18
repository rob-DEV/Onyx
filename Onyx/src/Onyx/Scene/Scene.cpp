#include "onyxpch.h"
#include "Scene.h"
#include "Entity.h"

#include <Onyx/Graphics/Renderer3D.h>

namespace Onyx {

	Scene::Scene()
	{
		m_CameraController = PerspectiveCameraController();

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity() {
		return Entity(m_ECSEntityRegistry.Create(), this);
	}

	void Scene::OnUpdate(Timestep timestep)
	{

		//2D


		//3D
		static const PerspectiveCamera& camera = m_CameraController.GetCamera();
		m_CameraController.OnUpdate(timestep);

		Renderer3D::BeginScene(camera);

		ECSView<MeshRendererComponent> view = m_ECSEntityRegistry.View<MeshRendererComponent>();
		
		for (int i = 0; i < view.size; ++i)
		{
			//render the meshes
			Renderer3D::DrawMesh(view.data[i].GetMesh(), { 0.0f,0.0f,0.0f }, { 5.0f,5.0f,5.0f });
		}
		Renderer3D::EndScene();
		Renderer3D::Flush();


	}

}
