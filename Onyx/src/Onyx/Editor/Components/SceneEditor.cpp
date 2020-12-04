#include "onyxpch.h"
#include "SceneEditor.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Editor/Components/Gizmo.h>
#include <Onyx/Editor/Renderer/EditorRenderer3D.h>
#include <Onyx/Editor/Components/SceneSerializer.h>
#include <Onyx/Editor/Components/EditorCameraController.h>

namespace Onyx {

	SceneEditor::SceneEditor() : 
		m_EditorCameraController(new EditorCameraController()),
		m_Scene(new Scene()),
		m_EditorGizmo(new Gizmo()),
		m_SelectedEntity(nullptr)
	{

	}

	SceneEditor::~SceneEditor()
	{
		InvalidateScene();

		delete m_EditorGizmo;
		delete m_Scene;
		delete m_EditorCameraController;
	}

	void SceneEditor::OnUpdate(Timestep ts)
	{
		m_EditorCameraController->OnUpdate(ts);

		RenderCommand::Clear();
		
		EditorRenderer3D::BeginScene(m_EditorCameraController->GetCamera());

		EditorRenderer3D::DrawScene(m_Scene);

		EditorRenderer3D::EndScene();
	}

	SceneData SceneEditor::NewScene()
	{
		InvalidateScene();
		m_Scene = new Scene();
		return m_Scene->m_SceneData;
	}

	SceneData SceneEditor::OpenScene(const char* filePath)
	{
		InvalidateScene();
		
		m_Scene = SceneSerializer::DeSerialize(filePath);


		
		Model* cube = ModelLoader::Load("Scene_Name_Placeholder", "res/models/Sponza/sponza.obj");

		for (Entity* e : m_Scene->m_Entities) {

			TransformComponent& t = e->GetComponent<TransformComponent>();
			t.Scale = glm::vec3(0.01f);

			MeshRendererComponent a = MeshRendererComponent(cube->GetMeshes());

			//Static mesh testing, static batch if Entity is marked as static
			e->m_Static = true;

			e->AddComponent<MeshRendererComponent>(a);
		}

		if (m_Scene == nullptr) {
			ONYX_ERROR("SceneEditor ERROR: Scene was nullptr");
		}

		return m_Scene->m_SceneData;
	}

	bool SceneEditor::SaveScene(const char* filePath)
	{
		SceneSerializer::Serialize(m_Scene, filePath);
		return true;
	}

	std::vector<Entity*> SceneEditor::GetAllEntitiesTest()
	{
		return m_Scene->m_Entities;
	}

	void SceneEditor::SetSelectedEntity(uint32_t id)
	{
		for (auto e : GetAllEntitiesTest())
		{
			if (e->GetID() == id) {
				m_SelectedEntity = e;
				TransformComponent& t = e->GetComponent<TransformComponent>();
				m_EditorGizmo->m_Transform.Position = t.Position;
			}

		}
	}

	void SceneEditor::InvalidateScene()
	{
		//TODO: Cleanup all entities and scene data
		//Cleanup Entt data
		for (auto e : m_Scene->m_Entities)
		{
			delete e;
		}
		m_Scene->m_Entities.clear();

		delete m_Scene;
	}

}