#include "onyxpch.h"
#include "EditorRenderer.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Editor/Components/Gizmo.h>
#include <Platform/OpenGL/OpenGLRenderer3D.h>

namespace Onyx {

	void EditorRenderer::BeginScene(const Camera& camera)
	{
		RenderCommand::Clear();
		Renderer3D::BeginScene(camera);
	}

	void EditorRenderer::EndScene()
	{
		Renderer3D::EndScene();
	}

	void EditorRenderer::Flush()
	{
		Renderer3D::Flush();
	}

	void EditorRenderer::DrawScene(const Scene* scene)
	{
		Renderer3D::DrawScene(scene);
	}

	void EditorRenderer::DrawGizmo(const Gizmo* gizmo)
	{
		//Draw Gizmo
		for (auto mesh : gizmo->m_ActiveModel->m_Meshes) {
			Renderer3D::DrawMesh(mesh, glm::vec3(0.0f), glm::vec3(1.0f));
		}
	}

}