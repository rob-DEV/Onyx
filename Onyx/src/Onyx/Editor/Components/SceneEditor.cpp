#include "onyxpch.h"
#include "SceneEditor.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Editor/Components/Gizmo.h>
#include <Onyx/Editor/Components/SceneSerializer.h>
#include <Onyx/Editor/Components/SceneEditorSelector.h>

#include <Platform/OpenGL/OpenGLFramebuffer.h>

#include <Onyx/Editor/Core/EditorRenderer.h>

namespace Onyx {

	SceneEditor::SceneEditor() : 
		m_EditorCameraController(new FirstPersonCameraController()),
		m_Scene(new Scene()),
		m_EditorGizmo(new Gizmo()),
		m_SelectedEntity(nullptr),
		m_SceneSelector(new SceneEditorSelector(this))
	{

	}

	SceneEditor::~SceneEditor()
	{
		delete m_EditorGizmo;
		delete m_Scene;
		delete m_EditorCameraController;
	}

	void SceneEditor::OnUpdate(Timestep ts)
	{
		m_EditorCameraController->OnUpdate(ts);
		m_SceneSelector->OnUpdate();

		RenderCommand::Clear();
		
		EditorRenderer::DrawScene(m_Scene, m_EditorCameraController->GetCamera());

		EditorRenderer::DrawGizmo(m_EditorGizmo, m_EditorCameraController->GetCamera());


	}

	bool SceneEditor::OpenScene(const char* filePath)
	{
		delete m_Scene;
		m_Scene = SceneSerializer::DeSerialize(filePath);

		
		Model* cube = ModelLoader::Load("Scene_Name_Placeholder", "res/models/Scene.obj");

// 		for (Entity* e : m_Scene->m_Entities) {
// 			MeshRendererComponent a = MeshRendererComponent(cube->GetMeshes().at(0));
// 			e->AddComponent<MeshRendererComponent>(a);
// 		}
		return true;
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

}