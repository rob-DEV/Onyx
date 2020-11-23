#include "onyxpch.h"
#include "EditorRenderer.h"

#include <Onyx/Scene/Scene.h>
#include <Onyx/Graphics/RendererAPI.h>
#include <Onyx/Graphics/RenderCommand.h>
#include <Onyx/Editor/Components/Gizmo.h>

#include <Onyx/Renderer/Renderer3D.h>

namespace Onyx {

	void EditorRenderer::DrawScene(const Scene* scene, const Camera& editorCamera)
	{
		
		Renderer3D::BeginScene(editorCamera);

		Renderer3D::DrawScene(scene);

		Renderer3D::EndScene();
		Renderer3D::Flush();


	}

	void EditorRenderer::DrawGizmo(const Gizmo* gizmo, const Camera& editorCamera)
	{

	}

}