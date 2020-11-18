#include "onyxpch.h"
#include "SceneEditorSelector.h"

//EDITOR RAY TESTING
#include <Onyx/Core/Input.h>
#include <Onyx/Physics/Ray.h>

#include <Onyx/Model/ModelLoader.h>
#include <Onyx/Graphics/Renderer3D.h>

namespace Onyx {

	SceneEditorSelector::SceneEditorSelector(FirstPersonCameraController* editorCamera)
		:
		m_EditorCamera(editorCamera)
	{
		m_MeshTest = ModelLoader::LoadFromFile("res/models/Scene.obj")->m_Meshes[1];
	}

	void SceneEditorSelector::OnUpdate()
	{
		Ray ray = m_EditorCamera->GetCamera().ScreenPointToRay();

		glm::vec3 pointOnRay = ray.GetPoint(10.0f);

		glm::vec2 pos = Input::GetMousePositionNormalized();

		printf("MOUSE: %.3f,%.3f\n", pos.x, pos.y);

		for (int i = 0; i < 20; ++i)
		{
			//Render cubes along the line
			Renderer3D::DrawMesh(m_MeshTest, pointOnRay, glm::vec3(0.1f));

		}

	}

}
