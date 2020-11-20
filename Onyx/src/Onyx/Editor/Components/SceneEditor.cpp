#include "onyxpch.h"
#include "SceneEditor.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Camera/FirstPersonCameraController.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Model/ModelLoader.h>
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
		m_SceneSelector(new SceneEditorSelector(m_EditorCameraController))
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

		EditorRenderer::BeginScene(m_EditorCameraController->GetCamera());

		EditorRenderer::DrawScene(m_Scene);


		EditorRenderer::DrawGizmo(m_EditorGizmo);

		EditorRenderer::EndScene();

		EditorRenderer::Flush();

	}

	bool SceneEditor::OpenScene(const char* filePath)
	{
		delete m_Scene;
		m_Scene = SceneSerializer::DeSerialize(filePath);

		
		Model* cube = ModelLoader::LoadFromFile("res/models/Scene.obj");

		for (Entity* e : m_Scene->m_Entities) {
			MeshRendererComponent a = MeshRendererComponent(cube->m_Meshes[1]);
			e->AddComponent<MeshRendererComponent>(a);
		}
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

}