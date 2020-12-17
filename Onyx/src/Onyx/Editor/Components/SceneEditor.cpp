#include "onyxpch.h"
#include "SceneEditor.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Editor/Components/Gizmo.h>
#include <Onyx/Editor/Renderer/EditorRenderer3D.h>
#include <Onyx/Editor/Components/SceneSerializer.h>
#include <Onyx/Editor/Components/EditorCameraController.h>

#include <Onyx/Core/Input.h>
#include <Onyx/Graphics/Shader.h>
#include <glad/glad.h>

#include <Onyx/Editor/Components/SceneEditorSelector.h>

#include <Onyx/Renderer/ScreenRenderer.h>

namespace Onyx {

	SceneEditor::SceneEditor() : 
		m_EditorCameraController(new EditorCameraController()),
		m_Scene(new Scene()),
		m_SelectedEntity(nullptr)
	{
		Gizmo::Init();
	}

	SceneEditor::~SceneEditor()
	{
		InvalidateScene();

		delete m_Scene;
		delete m_EditorCameraController;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	void SceneEditor::OnUpdate(Timestep ts)
	{
		m_EditorCameraController->OnUpdate(ts);

		RenderCommand::SetClearColor({ 0.2,0.2,0.2,1.0 });
 		RenderCommand::Clear();
		
		EditorRenderer3D::BeginScene(m_EditorCameraController->GetCamera());

		EditorRenderer3D::DrawScene(m_Scene);

		EditorRenderer3D::EndScene();

		

		Entity* selectedTest = GetSelectedEntity();

		if (selectedTest != nullptr) {
			//Do Gizmo operations
			

			TransformComponent& t = selectedTest->GetComponent<TransformComponent>();

			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), t.Rotation.x, { 1, 0, 0 })
				* glm::rotate(glm::mat4(1.0f), t.Rotation.y, { 0, 1, 0 })
				* glm::rotate(glm::mat4(1.0f), t.Rotation.z, { 0, 0, 1 });

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), t.Position)
				* rotation;
		}
	
		if (Input::IsKeyPressed(ONYX_KEY_1))
			Gizmo::SetState(GizmoState::TRANSFORM);
		else if (Input::IsKeyPressed(ONYX_KEY_2))
			Gizmo::SetState(GizmoState::ROTATE);
		else if (Input::IsKeyPressed(ONYX_KEY_3))
			Gizmo::SetState(GizmoState::SCALE);

		Gizmo::Manipulate(ts, m_EditorCameraController->GetCamera(), transform);

		Framebuffer* sceneFrambuffer = EditorRenderer3D::GetFramebuffer();
		Framebuffer* gizmoFrambuffer = Gizmo::GetFramebuffer();


		ScreenRenderer::RenderFramebufferTextureToScreen(sceneFrambuffer, 0);
		ScreenRenderer::RenderFramebufferTextureToScreen(gizmoFrambuffer, 0);
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

	Entity* SceneEditor::GetSelectedEntity()
	{
		for (auto e : GetAllEntitiesTest())
		{
			if (e->GetID() == SceneEditorSelector::GetSelectedEntityId()) {
				return e;
			}
		}

		return nullptr;
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