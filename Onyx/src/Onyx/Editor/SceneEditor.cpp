#include "onyxpch.h"
#include "SceneEditor.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Editor/Gizmo.h>
#include <Onyx/Camera/FirstPersonCameraController.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Editor/SceneSerializer.h>


namespace Onyx {

	SceneEditor::SceneEditor() : 
		m_EditorCamera(new FirstPersonCameraController()),
		m_Scene(new Scene()),
		m_EditorGizmo(new Gizmo())
	{
		//MeshRendererComponent m(ModelLoader::LoadFromFile("res/models/Scene.obj")->m_Meshes[0]);

	}

	SceneEditor::~SceneEditor()
	{
		delete m_EditorGizmo;
		delete m_Scene;
		delete m_EditorCamera;
	}

	void SceneEditor::OnUpdate(Timestep ts)
	{
		m_EditorCamera->OnUpdate(ts);

		//SCENE & RENDERING

		m_Scene->OnUpdate(ts);

		RenderCommand::SetClearColour(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer3D::BeginScene(m_EditorCamera->GetCamera());

		for (auto e : m_Scene->m_Entities)
		{
			if (e->HasComponent<TransformComponent>() && e->HasComponent<MeshRendererComponent>()) {
				TransformComponent& t = e->GetComponent<TransformComponent>();
				MeshRendererComponent& m = e->GetComponent<MeshRendererComponent>();

				Renderer3D::DrawMesh(m.GetMesh(), t.Position, t.Scale);
			}
		}

		//EDITOR

		if (m_Scene->m_Entities.size() > 0) {
			for (int i = 0; i < m_EditorGizmo->m_ActiveModel->m_Meshes.size(); ++i)
			{
				Renderer3D::DrawMesh(m_EditorGizmo->m_ActiveModel->m_Meshes[i], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
			}
		}

		Renderer3D::EndScene();
		Renderer3D::Flush();

	}

	bool SceneEditor::OpenScene(const char* filePath)
	{
		delete m_Scene;
		m_Scene = SceneSerializer::DeSerialize(filePath);
		return true;
	}

	bool SceneEditor::SaveScene(const char* filePath)
	{
		SceneSerializer::Serialize(m_Scene, filePath);
		return true;
	}

}